# FractalFlow: A 2D Fractal Puzzle-Exploration Game

## Overview
FractalFlow is an innovative 2D puzzle-exploration game built in C++ using the SFML library. Players navigate a fractal-inspired world by scaling and rotating recursive terrain segments to reveal hidden paths and collect energy orbs. The game combines exploration with fractal-based puzzle mechanics, offering a unique experience distinct from traditional puzzle or exploration games.

This open-source project is designed for developers, gamers, and educators interested in C++ game development, procedural generation, and fractal mathematics. By sponsoring FractalFlow via GitHub Sponsors, you support new features, level designs, and educational resources for the community.

## Features
- **Fractal Terrain Manipulation**: Scale and rotate recursive terrain to uncover hidden paths.
- **Procedural Levels**: Each level generates unique fractal patterns for replayability.
- **Minimalist Visuals**: Clean 2D graphics with glowing fractal effects.
- **Cross-Platform**: Runs on Windows, macOS, and Linux via SFML.
- **Modular Codebase**: Well-structured C++ code for easy extension and learning.

## Getting Started

### Prerequisites
- **C++ Compiler**: GCC, Clang, or MSVC with C++17 support.
- **SFML Library**: Version 2.5.1 or later (install via [SFML's official site](https://www.sfml-dev.org/) or package manager).
- **CMake**: Version 3.10 or later for building.

### Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/fractalflow.git
   cd fractalflow
   ```
2. Create a build directory:
   ```bash
   mkdir build && cd build
   ```
3. Configure with CMake:
   ```bash
   cmake ..
   ```
4. Build the project:
   ```bash
   cmake --build .
   ```
5. Run the game:
   ```bash
   ./FractalFlow
   ```

## Gameplay
- **Objective**: Collect all energy orbs and reach the exit by manipulating fractal terrain.
- **Controls**:
  - **WASD**: Move the player.
  - **Arrow Keys**: Select a terrain segment.
  - **Q/E**: Scale terrain up/down.
  - **R**: Rotate selected terrain.
  - **Space**: Reset level.
  - **Esc**: Pause or exit.
- **Mechanics**: Scale and rotate terrain segments to align paths and reveal orbs. Each manipulation affects recursive sub-layers, requiring strategic planning.

## Project Structure
- `src/main.cpp`: Game entry point and main loop.
- `src/Entity.hpp`: Base class for game entities (player, orbs, terrain).
- `src/Game.hpp`: Core game logic, fractal terrain generation, and rendering.
- `assets/`: Placeholder for textures/fonts (add your own or use SFML defaults).

## Contributing
Contributions are welcome! Fork the repo, create a feature branch, and submit a pull request. For major changes, open an issue to discuss your ideas.

## Sponsorship
Support FractalFlow’s development through [GitHub Sponsors](https://github.com/sponsors/yourusername)! Your contributions fund:
- New fractal algorithms and level designs.
- Enhanced terrain manipulation mechanics.
- Tutorials for C++ and procedural generation.
- Optimizations for broader platform support.

## License
Licensed under the MIT License. See [LICENSE](LICENSE) for details.

## Acknowledgments
- Built with [SFML](https://www.sfml-dev.org/) for graphics and input.
- Inspired by fractal mathematics and exploration puzzles.
- Thanks to the open-source community for feedback and inspiration.

---

**Sponsor FractalFlow to explore the infinite possibilities of fractal gaming!**