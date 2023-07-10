#ifndef SNAKE_HPP_
#define SNAKE_HPP_

#include <SFML/Graphics.hpp>
#include <string>
#include <random>
#include <array>

constexpr const int height = 20;
constexpr const int width = 30;
constexpr const int cubeSize = 16;

struct Snake {
    int x;
    int y;
};

struct Apple {
    int x;
    int y;
};

enum class Arrow {
    down = 0,
    left = 1,
    right = 2,
    up = 3
};

void tick(std::array<Snake, 100>&, Arrow, int&);
void move(std::array<Snake, 100>&, Arrow);
void check(std::array<Snake, 100>&, Apple&, int&);

#endif //SNAKE_HPP_