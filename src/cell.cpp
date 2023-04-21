#include <cell.hpp>
#include <stdint.h>
#include <utils.hpp>

int get_neighbours(std::vector<std::vector<struct cell>> &world, Vector2 pos, int type) {
    int count = 0;
    
    for (int x = pos.x - 1; x < pos.x + 1; x++) {
		if (x < 0 || x > COLUMNS)
			continue;

        for (int y = pos.y - 1; y < pos.y + 1; y++) {
            if (x == pos.x && y == pos.y)
                continue;
            if (world[x][y].type == type && world[x][y].alive)
                ++count;
        }   
    }    

    return count;
}


void tick_cells(std::vector<std::vector<struct cell>> &world, Vector2 pos, int type) {
    for (size_t x = 0; x < COLUMNS; x++) {
        for (size_t y = 0; y < ROWS; y++) {
            world[x][y].alive = (get_neighbours(world, pos, type) == 3);
        }
    }
}
