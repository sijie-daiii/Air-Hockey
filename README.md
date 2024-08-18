# Air Hockey Game

Welcome to the Air Hockey Game, a text-based simulation of the classic air hockey game built using C++ and the ncurses library. This project simulates a two-player air hockey game where players can control sliders (paddles) to compete against each other.

## Table of Contents

- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Controls](#controls)
- [Game Modes](#game-modes)
- [File Structure](#file-structure)
- [Contributing](#contributing)
- [License](#license)
- [Credits](#credits)

## Features

- **Text-Based UI**: Uses the ncurses library to create an interactive text-based user interface.
- **Multiple Difficulty Levels**: Players can choose between Easy, Medium, and Hard difficulty levels.
- **Customizable Gameplay**: Set slider size, goal area width, and number of sets.
- **Obstructions in Hard Mode**: Increase the challenge with obstructions that accelerate the ball when hit.
- **Save and Load Game**: Save the current game state and resume later.
- **Top 10 Scores**: Track and display the top 10 game records.

## Installation

### Prerequisites

- **C++ Compiler**: Make sure you have a C++ compiler installed (e.g., `g++`).
- **ncurses Library**: This game requires the ncurses library for terminal-based UI. Install it using your package manager:
  - **Ubuntu/Debian**: `sudo apt-get install libncurses5-dev libncursesw5-dev`
  - **Fedora**: `sudo dnf install ncurses-devel`
  - **MacOS**: `brew install ncurses`

### Cloning the Repository

```bash
git clone https://github.com/sijie-daiii/air-hockey-game.git
cd air-hockey-game
```

### Building the Game

Use the `Makefile` to compile the project:

```bash
make
```

This will create an executable named `air_hockey`.

## Usage

### Running the Game

After building, run the game with:

```bash
./air_hockey
```

### Game Flow

1. The game will start with a welcome screen and instructions.
2. Select the difficulty level.
3. Customize your game by setting slider size, goal area width, and the number of sets.
4. Play the game using the controls below.

### Saving and Loading

- The game automatically saves your progress at the end of each set.
- The top 10 scores are saved and can be viewed at the end of the game.

## Controls

- **Bottom Player (Slider)**
  - Move Left: `Left Arrow`
  - Move Right: `Right Arrow`
  - Move Up: `Up Arrow`
  - Move Down: `Down Arrow`
  
- **Top Player (Slider)**
  - Move Left: `A`
  - Move Right: `D`
  - Move Up: `W`
  - Move Down: `S`

- **Other Controls**
  - Pause/Resume: `P`
  - Quit: `Q`
  - Increase Slider Size: `+`
  - Decrease Slider Size: `-`

## Game Modes

- **Easy**: Basic gameplay with a slow-moving ball.
- **Medium**: Faster ball speed, no obstructions.
- **Hard**: Fastest ball speed with added obstructions that affect the ball's behavior.

## File Structure

- **`air_hockey.cpp`**: Main game logic.
- **`ball.cpp`**: Manages the ball's behavior.
- **`slider.cpp`**: Handles player slider (paddle) movement.
- **`zone.cpp`**: Manages the game area (zone) boundaries and goals.
- **`score.cpp`**: Manages score saving/loading and top 10 score records.
- **`key.cpp`**: Handles user input via keyboard.
- **`util.cpp`**: Contains utility functions like random number generation.
- **`Makefile`**: Used for compiling and linking the game.

## Contributing

Contributions are welcome! Please follow these steps:

1. Fork the repository.
2. Create a new branch for your feature or bugfix.
3. Commit your changes and push to your branch.
4. Submit a pull request with a description of your changes.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Credits

- **Developed by**: [Your Name](https://github.com/your-username)
- **Special Thanks to**: The ncurses library community and all contributors.

---

Feel free to customize the content, especially under "Credits" and "Contributing" sections, to better fit your project and team's structure. This README template should give potential users and contributors a clear understanding of your project, how to install and use it, and how they can contribute.