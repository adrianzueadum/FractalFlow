#ifndef GAME_HPP
#define GAME_HPP
#include "Entity.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <random>

class Game {
private:
    sf::RenderWindow& window;
    std::vector<std::vector<std::unique_ptr<Entity>>> terrain; // 2D grid of terrain segments
    std::vector<std::unique_ptr<Entity>> orbs; // Energy orbs
    std::unique_ptr<Entity> player;
    sf::Vector2i selectedSegment;
    std::mt19937 rng;
    bool isExitActive;

    void generateTerrain();

public:
    Game(sf::RenderWindow& win);
    void handleEvents();
    void update(float deltaTime);
    void render();
};

#endif // GAME_HPP
