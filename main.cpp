#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <stdexcept>
#include <chrono>
#include <thread>

class Paddle {
public:
    sf::Sprite sprite;

    Paddle(sf::Texture& texture) {
        sprite.setTexture(texture);
    }

    void setPosition(float x, float y) {
        sprite.setPosition(x, y);
    }

    void move(float offsetX, float offsetY) {
        sprite.move((0.5*offsetX), (0.5*offsetY));
    }
};

class Ball {
public:
    sf::CircleShape shape;

    Ball(float radius) {
        shape.setRadius(radius);
        shape.setFillColor(sf::Color::Red);
    }

    void setPosition(float x, float y) {
        shape.setPosition(x, y);
    }

    void move(float offsetX, float offsetY) {
        shape.move((0.5*offsetX), (0.5*offsetY));
    }
};

class Brick {
public:
    sf::Sprite sprite;

    Brick(sf::Texture& texture) {
        sprite.setTexture(texture);
    }

    void setPosition(float x, float y) {
        sprite.setPosition(x, y);
    }
};

class Menu {
public:
    sf::Text startText;
    sf::Text aboutUsText;
    sf::Text quitText;

    Menu(sf::Font& font) {
        startText.setFont(font);
        startText.setCharacterSize(40);
        startText.setFillColor(sf::Color::White);
        startText.setString("Start Game");
        startText.setPosition(50, 300);

        aboutUsText.setFont(font);
        aboutUsText.setCharacterSize(40);
        aboutUsText.setFillColor(sf::Color::White);
        aboutUsText.setString("About Us");
        aboutUsText.setPosition(50, 400);

        quitText.setFont(font);
        quitText.setCharacterSize(40);
        quitText.setFillColor(sf::Color::White);
        quitText.setString("Quit Game");
        quitText.setPosition(50, 500);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(startText);
        window.draw(aboutUsText);
        window.draw(quitText);
    }

    int handleInput(sf::RenderWindow& window) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                if (startText.getGlobalBounds().contains(mousePosition)) {
                    return 1; // Start Game
                } else if (aboutUsText.getGlobalBounds().contains(mousePosition)) {
                    return 2; // About Us
                } else if (quitText.getGlobalBounds().contains(mousePosition)) {
                    return 3; // Quit Game
                }
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::BackSpace) {
                    return 4; // Return to main menu
                }
            }
        }

        return 0; // No selection made
    }
};

void drawBlinkingText(sf::RenderWindow& window, sf::Text& text, int blinkCount) {
    for (int i = 0; i < blinkCount; ++i) {
        window.clear();
        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        window.clear();
        window.draw(text);
        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode::getFullscreenModes()[0], "Brick Breaker Game", sf::Style::Fullscreen);

    try {
        sf::Texture backgroundTexture;
        if (!backgroundTexture.loadFromFile("background.jpg")) {
            throw std::runtime_error("Unable to load background image");
        }
        sf::Sprite backgroundSprite(backgroundTexture);

        sf::Music backgroundMusic;
        if (!backgroundMusic.openFromFile("collision_sound.wav")) {
            throw std::runtime_error("Unable to load background music");
        }
        backgroundMusic.setLoop(true);
        backgroundMusic.play();

        sf::SoundBuffer gameOverBuffer;
        if (!gameOverBuffer.loadFromFile("game_over_sound.wav")) {
            throw std::runtime_error("Unable to load game over sound");
        }
        sf::Sound gameOverSound;
        gameOverSound.setBuffer(gameOverBuffer);

        // Load paddle texture
        sf::Texture paddleTexture;
        if (!paddleTexture.loadFromFile("paddle_texture.png")) {
            throw std::runtime_error("Unable to load paddle texture");
        }

        Paddle paddle(paddleTexture);
        paddle.setPosition(350, window.getSize().y - 60);

        Ball ball(15);
        ball.setPosition(400, window.getSize().y - 100);
        float ballSpeedX = 2.0f;
        float ballSpeedY = -2.0f;

        // Load brick texture
        sf::Texture brickTexture;
        if (!brickTexture.loadFromFile("brick_texture.png")) {
            throw std::runtime_error("Unable to load brick texture");
        }

        const int numBricksX = 12;
        const int numBricksY = 5;
        std::vector<Brick> bricks;

        // Adjust the size of bricks
        double brickWidth = 0.2;
        double brickHeight = 0.1;

        for (int i = 0; i < numBricksX; ++i) {
            for (int j = 0; j < numBricksY; ++j) {
                Brick brick(brickTexture);
                brick.setPosition(i * (brickWidth + 160) + 10, j * (brickHeight + 80) + 20);

                bricks.push_back(brick);
            }
        }

        // Adjust the size of the paddle
        float paddleWidth = 0.0002;
        float paddleHeight = 0.00001;

        sf::RectangleShape redLine(sf::Vector2f(window.getSize().x, 50));
        redLine.setFillColor(sf::Color::Red);
        redLine.setPosition(0, window.getSize().y - 10);

        bool gameover = false;
        int score = 0;

        sf::Font font;
        if (!font.loadFromFile("ALIEN5.ttf")) {
            throw std::runtime_error("Unable to load font");
        }

        sf::Text scoreText;
        scoreText.setFont(font);
        scoreText.setCharacterSize(80);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setString("Score: 0");
        scoreText.setPosition(10, 10);

        sf::Text gameOverText;
        gameOverText.setFont(font);
        gameOverText.setCharacterSize(80);
        gameOverText.setFillColor(sf::Color::White);
        gameOverText.setString("Game Over");
        sf::FloatRect gameOverBounds = gameOverText.getLocalBounds();
        gameOverText.setOrigin(gameOverBounds.left + gameOverBounds.width / 2, gameOverBounds.top + gameOverBounds.height / 2);
        gameOverText.setPosition(window.getSize().x / 2, window.getSize().y / 2);

        Menu menu(font);

        int menuChoice = 0; // 0: No selection, 1: Start Game, 2: About Us, 3: Quit Game

        while (window.isOpen() && menuChoice == 0) {
            menu.draw(window);
            window.display();
            menuChoice = menu.handleInput(window);
        }

        if (menuChoice == 1) {
            // Start Game
            while (window.isOpen() && !gameover) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window.close();
                    }
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && paddle.sprite.getPosition().x > 0) {
                    paddle.move(-10, 0);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
                    paddle.sprite.getPosition().x + paddle.sprite.getGlobalBounds().width < window.getSize().x) {
                    paddle.move(10, 0);
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    // Return to main menu
                    gameover = true;
                    menuChoice = 0;
                }

                ball.move(ballSpeedX, ballSpeedY);

                if (ball.shape.getPosition().x < 0 || ball.shape.getPosition().x + ball.shape.getRadius() * 0.1 > window.getSize().x) {
                    ballSpeedX = -ballSpeedX;
                }
                if (ball.shape.getPosition().y < 0) {
                    ballSpeedY = -ballSpeedY;
                }

                if (ball.shape.getGlobalBounds().intersects(paddle.sprite.getGlobalBounds())) {
                    ballSpeedY = -ballSpeedY;
                }

                for (auto& brick : bricks) {
                    if (ball.shape.getGlobalBounds().intersects(brick.sprite.getGlobalBounds())) {
                        brick.setPosition(-100, -100);
                        ballSpeedY = -ballSpeedY;

                        // Increase score when the ball hits a brick
                        score++;
                        // Update the score text
                        scoreText.setString("Score: " + std::to_string(score));
                    }
                }

                // Check if all bricks are destroyed
                bool allBricksDestroyed = true;
                for (const auto& brick : bricks) {
                    if (brick.sprite.getPosition().x != -100 || brick.sprite.getPosition().y != -100) {
                        allBricksDestroyed = false;
                        break;
                    }
                }

                if (allBricksDestroyed) {
                    // All bricks are destroyed, level cleared
                    gameover = true;
                    backgroundMusic.stop();
                    // Additional actions for level cleared, if needed
                }

                if (ball.shape.getPosition().y + ball.shape.getRadius() * 2 > redLine.getPosition().y) {
                    gameover = true;
                    backgroundMusic.stop();
                    gameOverSound.play();

                    // Display the final score in the center with blinking effect
                    scoreText.setPosition(window.getSize().x / 2 - 100, window.getSize().y / 2 - 40);
                    drawBlinkingText(window, scoreText, 5);
                }

                window.clear();
                window.draw(backgroundSprite);
                window.draw(paddle.sprite);
                window.draw(ball.shape);
                for (const auto& brick : bricks) {
                    window.draw(brick.sprite);
                }
                window.draw(redLine);

                // Draw the score during the game, only if the game is not over
                if (!gameover) {
                    window.draw(scoreText);
                }

                // Draw "Game Over" text only when the game is over
                if (gameover) {
                    window.draw(gameOverText);
                }

                window.display();
            }
        } else if (menuChoice == 2) {
            // About Us
            sf::Text aboutUs;
            aboutUs.setFont(font);
            aboutUs.setCharacterSize(30);
            aboutUs.setFillColor(sf::Color::White);
            aboutUs.setString("Authors:\nAhsan Raza\nHassan zaib jadoon\nMutahhar Fayyaz");
            aboutUs.setPosition(50, 300);

            while (window.isOpen()) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window.close();
                    }
                    else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::BackSpace) {
                        // Return to the main menu when BackSpace is pressed
                        return 0;
                    }
                }

                window.clear();
                window.draw(backgroundSprite);
                window.draw(aboutUs);

                // Draw "Back" text
                sf::Text backText;
                backText.setFont(font);
                backText.setCharacterSize(30);
                backText.setFillColor(sf::Color::White);
                backText.setString("Back (Press Backspace)");
                backText.setPosition(50, 550);
                window.draw(backText);

                window.display();
            }
        } else if (menuChoice == 3) {
            // Quit Game
            window.close();
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}
