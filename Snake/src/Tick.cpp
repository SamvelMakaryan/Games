#include "Snake.hpp"

void tick(std::array<Snake, 100>& snake, Arrow arrow, int& snakeSize) {
    for (int i = snakeSize; i > 0; --i) {
        snake[i].x = snake[i - 1].x;
        snake[i].y = snake[i - 1].y;
    }
    move(snake, arrow);
}

void move(std::array<Snake, 100>& snake, Arrow arrow) {
    switch (arrow) {
    case Arrow::down:
        snake[0].y += 1;
        break;        
    case Arrow::up:
        snake[0].y -= 1;
        break;        
    case Arrow::left:
        snake[0].x -= 1;
        break;        
    case Arrow::right:
        snake[0].x += 1;
        break;

    }
}

void check(std::array<Snake, 100>& snake, Apple& apple, int& snakeSize) {
    if ((snake[0].x == apple.x) && (snake[0].y == apple.y)) {
        ++snakeSize;
        std::random_device rd;
        apple.x = rd() % width;
        apple.y = rd() % height;    
    }
    if (snake[0].x > width) {
        snake[0].x = 0;
    }
    if (snake[0].y > height) {
        snake[0].y = 0;
    }
    if (snake[0].x < 0) {
        snake[0].x = width;
    }
    if (snake[0].y < 0) {
        snake[0].y = height;
    }
    for (int i = 1; i < snakeSize; ++i) {
        if ((snake[0].x == snake[i].x) && (snake[0].y == snake[i].y)) {
            snakeSize = i;
        }
    }
}

