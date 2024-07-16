# Brick Breaker Game

[![GitHub issues](https://img.shields.io/github/issues/hzjadoon/Brick-Breaker-Game-)](https://github.com/hzjadoon/Brick-Breaker-Game-/issues)
[![GitHub forks](https://img.shields.io/github/forks/hzjadoon/Brick-Breaker-Game-)](https://github.com/hzjadoon/Brick-Breaker-Game-/network)
[![GitHub stars](https://img.shields.io/github/stars/hzjadoon/Brick-Breaker-Game-)](https://github.com/hzjadoon/Brick-Breaker-Game-/stargazers)
[![GitHub license](https://img.shields.io/github/license/hzjadoon/Brick-Breaker-Game-)](https://github.com/hzjadoon/Brick-Breaker-Game-/blob/main/LICENSE)
[![Follow on GitHub](https://img.shields.io/github/followers/hzjadoon?label=Follow&style=social)](https://github.com/hzjadoon)

## Table of Contents
- [Description](#description)
- [Features](#features)
- [Controls](#controls)
- [Installation](#installation)
- [Contributing](#contributing)
- [License](#license)
- [Object-Oriented Programming Concepts](#object-oriented-programming-concepts)
- [Algorithm](#algorithm)
- [Game Logic](#game-logic)
- [Flowchart](#flowchart)
- [Contact](#contact)

## Description
Welcome to the Brick Breaker Game repository! This project is a classic arcade game built using SFML (Simple and Fast Multimedia Library) in C++. The game involves breaking bricks using a paddle and a bouncing ball.

## Features

- Fullscreen mode for immersive gameplay.
- Simple and intuitive controls.
- Background music and sound effects.
- Score tracking.
- Main menu with options to start the game, view credits, and quit.
- Game over and level completion conditions.

## Controls

- **Left Arrow Key**: Move paddle left.
- **Right Arrow Key**: Move paddle right.
- **Escape Key**: Return to the main menu.

## Installation
To run the Brick Breaker Game, follow these steps:
1. **Clone the repository**
    ```bash
    git clone https://github.com/hzjadoon/Brick-Breaker-Game-.git
    cd Brick-Breaker-Game-
    ```
2. **Compile the game**
    Ensure you have SFML installed. You can compile the game using the following command:
    ```bash
    g++ -o brick_breaker main.cpp -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
    ```

## Contributing
Contributions are welcome! If you have suggestions for improvements, please follow these steps:
1. **Fork the repository.**
2. **Create a new branch** (`git checkout -b feature-branch`).
3. **Commit your changes** (`git commit -am 'Add new feature'`).
4. **Push to the branch** (`git push origin feature-branch`).
5. **Create a new Pull Request.**

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Object-Oriented Programming Concepts

The game is designed using several OOP principles:

1. **Classes and Objects**: The main game components such as `Paddle`, `Ball`, `Brick`, and `Menu` are implemented as classes.
2. **Encapsulation**: Each class encapsulates its data and behavior, providing a clear interface for interaction.
3. **Inheritance and Polymorphism**: Although not heavily used in this example, the design allows for future extension where these concepts can be applied.

### Class Descriptions

- **Paddle**: Represents the player's paddle. Handles movement and position updates.
- **Ball**: Represents the ball that bounces around the screen. Manages movement and collision detection.
- **Brick**: Represents individual bricks that the ball will break.
- **Menu**: Manages the game menu, including the start, about us, and quit options.

## Algorithm

1. Initialize the game window in fullscreen mode.
2. Load textures, sounds, and fonts.
3. Create game objects: paddle, ball, and bricks.
4. Display the main menu and handle user input.
5. If the game starts, enter the game loop:
    - Handle user input for paddle movement.
    - Update ball position and check for collisions:
      - With walls (change ball direction).
      - With paddle (change ball direction).
      - With bricks (remove brick, increase score, change ball direction).
    - Check for game over conditions (ball falls below paddle).
    - Check for level completion (all bricks destroyed).
6. Display game over or level completion screen as appropriate.
7. Handle "About Us" and "Quit Game" options in the main menu.

# Game Logic

## Initialization
- Initialize game window
- Load textures, sounds, and fonts
- Create paddle, ball, and bricks

## Main Game Loop

### While game is running:
1. **If in main menu:**
    - Display menu
    - Handle menu input
    - If "Start Game" selected:
        - Enter game loop

2. **Else if in game loop:**
    - Handle paddle movement input
    - Update ball position
    - Check for ball collision with walls
    - Check for ball collision with paddle
    - Check for ball collision with bricks
    - If all bricks are destroyed:
        - Display level complete message
        - Break game loop
    - If ball falls below paddle:
        - Display game over message
        - Break game loop
    - Render game objects

3. **Else if in "About Us" screen:**
    - Display "About Us" information
    - Handle "Back to Menu" input

4. **Else if "Quit Game" selected:**
    - Exit game


## Flowchart

```plaintext
           +--------------------+
           | Start              |
           +--------------------+
                    |
                    v
   +----------------------------------+
   | Initialize game window, load     |
   | textures, sounds, fonts, and     |
   | create game objects              |
   +----------------------------------+
                    |
                    v
           +--------------------+
           | Display Main Menu  |
           +--------------------+
                    |
                    v
         +----------------------+
         | Handle Menu Input    |
         +----------------------+
                    |
         +----------+----------+
         |                     |
         v                     v
+-------------------+  +-----------------+
| Start Game        |  | Show About Us   |
+-------------------+  +-----------------+
         |                     |
         v                     v
+-------------------+  +-----------------+
| Enter Game Loop   |  | Handle About Us |
+-------------------+  +-----------------+
         |                     |
         v                     v
+-------------------+  +-----------------+
| Handle Input,     |  | Return to Menu  |
| Update Positions  |  +-----------------+
| and Collisions    |
+-------------------+
         |
         v
+-------------------+
| Check for Win or  |
| Game Over         |
+-------------------+
         |
         v
+-------------------+
| Display Win or    |
| Game Over Screen  |
+-------------------+
         |
         v
+-------------------+
| Return to Menu    |
+-------------------+

 ```

## Contact
For any inquiries or feedback, feel free to reach out:
- **GitHub**: [hzjadoon](https://github.com/hzjadoon)
- **Email**: [hassanzaibjadoon2004@gmail.com](mailto:hassanzaibjadoon2004@gmail.com)
