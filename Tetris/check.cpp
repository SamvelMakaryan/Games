#include "Tetris.hpp"

bool check(std::array<std::array<int, width>, height> field, std::array<Point, 4> currentPosition) {
	for (int i = 0; i < 4; i++) {
	if (currentPosition[i].x < 0 || currentPosition[i].x >= width || currentPosition[i].y >= height) {
			return false;
		}
		if (field[currentPosition[i].y][currentPosition[i].x]) {
			return false;
		}
	}
	return true;
}
