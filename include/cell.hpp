#ifndef CELL_HPP
#define CELL_HPP

#include <raylib.h>
#include <utils.hpp>
#include <vector>

enum team {
	TEAM_NONE = 0,
	TEAM_BLUE,
	TEAM_RED
};

#define COLOR_DEAD \
	{ \
		0, 0, 0, 0 \
	}
#define COLOR_RED \
	{ \
		255, 0, 0, 0 \
	}
#define COLOR_BLUE \
	{ \
		0, 0, 255, 0 \
	}

typedef int Cell;

int get_cell(std::vector<std::vector<Cell>>& world, Vector2I pos);
void set_cell(std::vector<std::vector<Cell>>& world, Vector2I pos, int type);

CellCount get_neighbours(std::vector<std::vector<Cell>>& world, Vector2I pos);
void tick_cell(std::vector<std::vector<Cell>>& world,
	       std::vector<std::vector<Cell>>& world_copy, Vector2I pos);
CellCount count_cells(std::vector<std::vector<Cell>>& world);

#endif
