#include "Game.hpp"
#include <algorithm>
#include <cmath>

class Player : public Entity {
private:
    sf::CircleShape shape;
    sf::Vector2f position;
    bool active;

public:
    Player(float x, float y) : position(x, y), active(true) {
        shape.setRadius(10.f);
        shape.setFillColor(sf::Color::Green);
        shape.setPosition(position);
    }

    void update(float deltaTime) override {}
    void render(sf::RenderWindow& window) const override {
        if (active) window.draw(shape);
    }
    sf::Vector2f getPosition() const override { return position; }
    void setPosition(const sf::Vector2f& pos) override { position = pos; shape.setPosition(pos); }
    bool isActive() const override { return active; }
    void scale(float factor) override {} // Player doesn't scale
    void rotate(float angle) override {} // Player doesn't rotate
};

class TerrainSegment : public Entity {
private:
    sf::RectangleShape shape;
    sf::Vector2f position;
    float scaleFactor;
    float rotation;
    bool active;

public:
    TerrainSegment(float x, float y) : position(x, y), scaleFactor(1.f), rotation(0.f), active(true) {
        shape.setSize(sf::Vector2f(50.f, 50.f));
        shape.setFillColor(sf::Color(50, 50, 50));
        shape.setPosition(position);
    }

    void update(float deltaTime) override {
        shape.setScale(scaleFactor, scaleFactor);
        shape.setRotation(rotation);
    }

    void render(sf::RenderWindow& window) const override {
        if (active) window.draw(shape);
    }

    sf::Vector2f getPosition() const override { return position; }
    void setPosition(const sf::Vector2f& pos) override { position = pos; shape.setPosition(pos); }
    bool isActive() const override { return active; }
    void scale(float factor) override { scaleFactor *= factor; if (scaleFactor < 0.5f) scaleFactor = 0.5f; if (scaleFactor > 2.f) scaleFactor = 2.f; }
    void rotate(float angle) override { rotation += angle; }
};

class Orb : public Entity {
private:
    sf::CircleShape shape;
    sf::Vector2f position;
    bool active;

public:
    Orb(float x, float y) : position(x, y), active(true) {
        shape.setRadius(5.f);
        shape.setFillColor(sf::Color::Yellow);
        shape.setPosition(position);
    }

    void update(float deltaTime) override {}
    void render(sf::RenderWindow& window) const override {
        if (active) window.draw(shape);
    }
    sf::Vector2f getPosition() const override { return position; }
    void setPosition(const sf::Vector2f& pos) override { position = pos; shape.setPosition(pos); }
    bool isActive() const override { return active; }
    void scale(float factor) override {} // Orbs don't scale
    void rotate(float angle) override {} // Orbs don't rotate
    void collect() { active = false; }
};

Game::Game(sf::RenderWindow& win) : window(win), selectedSegment(0, 0), rng(std::random_device{}()), isExitActive(false) {
    terrain.resize(5, std::vector<std::unique_ptr<Entity>>(5));
    generateTerrain();
    player = std::make_unique<Player>(300.f, 250.f);
    orbs.push_back(std::make_unique<Orb>(400.f, 200.f));
    orbs.push_back(std::make_unique<Orb>(350.f, 300.f));
}

void Game::generateTerrain() {
    std::uniform_real_distribution<float> dist(0.f, 1.f);
    for (int y = 0; y < 5; ++y) {
        for (int x = 0; x < 5; ++x) {
            terrain[y][x] = std::make_unique<TerrainSegment>(250.f + x * 50.f, 150.f + y * 50.f);
            if (dist(rng) < 0.3f) terrain[y][x]->scale(0.5f); // Random scaling for fractal effect
        }
    }
}

void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        } else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Space) {
                terrain.clear();
                terrain.resize(5, std::vector<std::unique_ptr<Entity>>(5));
                generateTerrain();
                player->setPosition(sf::Vector2f(300.f, 250.f));
                orbs.clear();
                orbs.push_back(std::make_unique<Orb>(400.f, 200.f));
                orbs.push_back(std::make_unique<Orb>(350.f, 300.f));
                selectedSegment = {0, 0};
                isExitActive = false;
            } else if (event.key.code == sf::Keyboard::Escape) {
                window.close();
            } else if (event.key.code == sf::Keyboard::W) {
                sf::Vector2f newPos = player->getPosition() + sf::Vector2f(0.f, -50.f);
                if (newPos.y >= 150.f) player->setPosition(newPos);
            } else if (event.key.code == sf::Keyboard::S) {
                sf::Vector2f newPos = player->getPosition() + sf::Vector2f(0.f, 50.f);
                if (newPos.y <= 350.f) player->setPosition(newPos);
            } else if (event.key.code == sf::Keyboard::A) {
                sf::Vector2f newPos = player->getPosition() + sf::Vector2f(-50.f, 0.f);
                if (newPos.x >= 250.f) player->setPosition(newPos);
            } else if (event.key.code == sf::Keyboard::D) {
                sf::Vector2f newPos = player->getPosition() + sf::Vector2f(50.f, 0.f);
                if (newPos.x <= 450.f) player->setPosition(newPos);
            } else if (event.key.code == sf::Keyboard::Up && selectedSegment.y > 0) {
                selectedSegment.y--;
            } else if (event.key.code == sf::Keyboard::Down && selectedSegment.y < 4) {
                selectedSegment.y++;
            } else if (event.key.code == sf::Keyboard::Left && selectedSegment.x > 0) {
                selectedSegment.x--;
            } else if (event.key.code == sf::Keyboard::Right && selectedSegment.x < 4) {
                selectedSegment.x++;
            } else if (event.key.code == sf::Keyboard::Q) {
                terrain[selectedSegment.y][selectedSegment.x]->scale(1.1f);
            } else if (event.key.code == sf::Keyboard::E) {
                terrain[selectedSegment.y][selectedSegment.x]->scale(0.9f);
            } else if (event.key.code == sf::Keyboard::R) {
                terrain[selectedSegment.y][selectedSegment.x]->rotate(45.f);
            }
        }
    }
}

void Game::update(float deltaTime) {
    player->update(deltaTime);
    for (auto& row : terrain) {
        for (auto& segment : row) {
            segment->update(deltaTime);
        }
    }
    for (auto& orb : orbs) {
        orb->update(deltaTime);
        if (orb->isActive() && std::hypot(player->getPosition().x - orb->getPosition().x, player->getPosition().y - orb->getPosition().y) < 15.f) {
            orb->collect();
        }
    }
    // Check if all orbs are collected
    bool allOrbsCollected = std::all_of(orbs.begin(), orbs.end(), [](const auto& orb) { return !orb->isActive(); });
    if (allOrbsCollected) isExitActive = true;
}

void Game::render() {
    window.clear(sf::Color::Black);

    // Draw terrain
    for (const auto& row : terrain) {
        for (const auto& segment : row) {
            segment->render(window);
        }
    }

    // Draw selected segment highlight
    sf::RectangleShape highlight(sf::Vector2f(50.f, 50.f));
    highlight.setFillColor(sf::Color::Transparent);
    highlight.setOutlineColor(sf::Color::Yellow);
    highlight.setOutlineThickness(2.f);
    highlight.setPosition(250.f + selectedSegment.x * 50.f, 150.f + selectedSegment.y * 50.f);
    window.draw(highlight);

    // Draw orbs
    for (const auto& orb : orbs) {
        orb->render(window);
    }

    // Draw exit
    sf::CircleShape exit(10.f);
    exit.setPosition(400.f, 350.f);
    exit.setFillColor(isExitActive ? sf::Color::Green : sf::Color::Red);
    window.draw(exit);

    // Draw player
    player->render(window);

    window.display();
}
