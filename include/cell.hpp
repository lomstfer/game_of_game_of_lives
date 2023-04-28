#ifndef CELL_HPP
#define CELL_HPP

#include <vector>
#include <raylib.h>
#include <utils.hpp>

enum team {
    TEAM_NONE = 0,
    TEAM_BLUE,
    TEAM_RED
};

#define COLOR_DEAD {0,0,0,0}
#define COLOR_RED {255,0,0,0}
#define COLOR_BLUE {0,0,255,0}

typedef int Cell;

int get_neighbours(std::vector<std::vector<Cell>> &world, Vec2Int pos);
void tick_cell(std::vector<std::vector<Cell>> &world, Vec2Int pos);
int who_won(std::vector<std::vector<Cell>> &world);

#endif