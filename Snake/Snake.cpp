#include "Snake.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(width * cubeSize, height * cubeSize),"Snake");
    sf::Texture redTexture;
    sf::Texture backgroundTexture;
    sf::Texture questionTexture;
    redTexture.loadFromFile("images/red.png");
    questionTexture.loadFromFile("images/background.png");
    sf::Sprite questionSprite(questionTexture);
    std::string backgroundColor;
    while (true) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            backgroundColor = "images/white.png";
            break;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            backgroundColor = "images/green.png";
            break;
        }
        window.clear();
        window.draw(questionSprite);
        window.display();
    }
    backgroundTexture.loadFromFile(backgroundColor);
    sf::Event event;
    sf::Sprite redSprite(redTexture);
    sf::Sprite backgroundSprite(backgroundTexture);
    std::array<Snake, 100> snake;
    Apple apple;
    Arrow arrow;
    sf::Clock clock;
    float timer = 0.0f;
    float delay = 0.1f;
    int snakeSize = 2;
    std::random_device rd;    
    apple.x = rd() % width;
    apple.y = rd() % height;
    while (window.isOpen()) {
        float currentTime = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += currentTime;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            arrow = Arrow::down;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            arrow = Arrow::up;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            arrow = Arrow::left;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            arrow = Arrow::right;
        }
        if ((snake[0].x == apple.x) && (snake[0].y == apple.y)) {
            ++snakeSize;
        }
        if (timer > delay) {
            timer = 0;
            tick(snake, arrow, snakeSize);
            check(snake, apple, snakeSize);
        }
        window.clear(sf::Color::White);
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                backgroundSprite.setPosition(i * cubeSize, j * cubeSize);
                window.draw(backgroundSprite);
            }
        }
        for (int i = 0; i < snakeSize; ++i) {
            redSprite.setPosition(snake[i].x * cubeSize, snake[i].y * cubeSize);
            window.draw(redSprite); 
        }
        redSprite.setPosition(apple.x * cubeSize, apple.y * cubeSize);
        window.draw(redSprite);
        window.display();
    }
}