#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <raylib.h>
#include <vector>

struct Vector2I {
	int x;
	int y;
};

struct CellCount {
	int blues;
	int reds;
};

#define LOG(...) std::cout << __VA_ARGS__ << std::endl;

#define WINDOW_WIDTH  1280
#define WINDOW_HEIGTH 720

#define BLOCK_SIZE 20
#define TICKS_PER_SECOND 1.f / 10.f
#define CELLS_PER_TURN 10
#define TICKS_PER_TURN 10

const int COLUMNS = WINDOW_WIDTH / BLOCK_SIZE;
const int ROWS = WINDOW_HEIGTH / BLOCK_SIZE;

Vector2 operator/(Vector2 v, float f);
Vector2 operator*(Vector2 v, float f);
std::ostream& operator<<(std::ostream& os, Vector2 v);
std::ostream& operator<<(std::ostream& os, Vector2 v);

#endif