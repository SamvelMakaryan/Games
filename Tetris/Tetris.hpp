#ifndef CHECK_HPP_
#define CHECK_HPP_
#include <array>

struct Point {
	int x;
	int y;
};

const constexpr int height = 20;
const constexpr int width = 10;

bool check(std::array<std::array<int, width>, height>, std::array<Point, 4>);

#endif //CHECK_HPP_