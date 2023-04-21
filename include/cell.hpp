#ifndef CELL_HPP
#define CELL_HPP

#include <vector>
#include <raylib.h>

struct cell {
    int type;
    bool alive;
};

int get_neighbours(std::vector<std::vector<cell>> &world, Vector2 pos);

void tick_cells(std::vector<std::vector<struct cell>> &world, Vector2 pos, int type);

#endif