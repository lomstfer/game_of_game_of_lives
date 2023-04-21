#ifndef UTILS_HPP
#define UTILS_HPP

#include <raylib.h>
#include <vector>
#include <iostream>
#include <cell.hpp>

#define LOG(...) std::cout << __VA_ARGS__ << std::endl;

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGTH 720

#define BLOCK_SIZE 10

const int COLUMNS = WINDOW_WIDTH / BLOCK_SIZE;
const int ROWS = WINDOW_HEIGTH / BLOCK_SIZE;

Vector2 operator/(Vector2 v, float f);
Vector2 operator*(Vector2 v, float f);
std::ostream& operator<<(std::ostream& os, Vector2 v);

int who_won(std::vector<std::vector<cell>> &world);

enum team {
    team_blue = 0,
    team_red
};

#endif