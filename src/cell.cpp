#include <cassert>
#include <stdint.h>

#include <cell.hpp>
#include <utils.hpp>

int get_cell(std::vector<std::vector<Cell>>& world, Vector2I pos) {
	return world[pos.y][pos.x];
}

void set_cell(std::vector<std::vector<Cell>>& world, Vector2I pos, int type) {
	world[pos.y][pos.x] = type;
	return;
}

CellCount get_neighbours(std::vector<std::vector<Cell>>& world, Vector2I pos) {
	int blue_count = 0;
	int red_count = 0;
	// Cell type = get_cell(world, pos);

	if (pos.x < 0 || pos.y < 0 || pos.x > COLUMNS || pos.y > ROWS) {
		printf("\x1b[31mBUG: get_neighbors: out of range: %d, "
		       "%d\x1b[m\n",
		       pos.x, pos.y);
		return {0, 0};
	}

	for (int x = pos.x - 1; x <= pos.x + 1; x++) {
		if (x < 0 || x >= COLUMNS)
			continue;

		for (int y = pos.y - 1; y <= pos.y + 1; y++) {
			if (y < 0 || y >= ROWS)
				continue;

			if (x == pos.x && y == pos.y)
				continue;

			int t = get_cell(world, {x, y});
			if (t == TEAM_BLUE)
				blue_count++;

			else if (t == TEAM_RED)
				red_count++;
		}
	}

	return {blue_count, red_count};
}

void tick_cell(std::vector<std::vector<Cell>>& world,
	       std::vector<std::vector<Cell>>& world_copy, Vector2I pos) {
	CellCount counts = get_neighbours(world_copy, pos);

	int blues = counts.blues;
	int reds = counts.reds;
	int total = reds + blues;
	Cell team;

	if (blues > reds) {
		team = TEAM_BLUE;
	} else {
		team = TEAM_RED;
	}

	switch (get_cell(world_copy, pos)) {
	case TEAM_NONE:
		if (total == 3)
			set_cell(world, pos, team);
		break;

	case TEAM_BLUE:
		if (blues != 2 && blues != 3) {
			if (total == 3 && team == TEAM_RED)
				set_cell(world, pos, TEAM_RED);
			else
				set_cell(world, pos, TEAM_NONE);
		}
		break;

	case TEAM_RED:
		if (reds != 2 && reds != 3) {
			if (total == 3 && team == TEAM_BLUE)
				set_cell(world, pos, TEAM_BLUE);
			else
				set_cell(world, pos, TEAM_NONE);
		}
		break;
	}
	return;
}

CellCount count_cells(std::vector<std::vector<Cell>>& world) {
	int blue_count = 0;
	int red_count = 0;

	for (int x = 0; x < COLUMNS; x++) {
		for (int y = 0; y < ROWS; y++) {

			switch (get_cell(world, {x, y})) {
			case TEAM_RED:
				red_count++;
				break;

			case TEAM_BLUE:
				blue_count++;
				break;
			}
		}
	}
	return {blue_count, red_count};
}