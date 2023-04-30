#ifndef UTILS_HPP
#define UTILS_HPP

#include <raylib.h>
#include <vector>
#include <iostream>

struct Vector2I {
    int x;
    int y;
};

#define LOG(...) std::cout << __VA_ARGS__ << std::endl;

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGTH 720

#define BLOCK_SIZE 10
// struct timespec, hello?
#define TICKS_PER_SECOND 1.f / 3.f

#define COLUMNS WINDOW_WIDTH / BLOCK_SIZE
#define ROWS WINDOW_HEIGTH / BLOCK_SIZE

Vector2 operator/(Vector2 v, float f);
Vector2 operator*(Vector2 v, float f);
std::ostream& operator<<(std::ostream& os, Vector2 v);
std::ostream& operator<<(std::ostream& os, Vector2 v);

#endif