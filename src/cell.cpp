#include <cell.hpp>
#include <stdint.h>
#include <utils.hpp>
#include <cassert>

int get_neighbours(std::vector<std::vector<Cell>> &world, Vec2Int pos) {
    int count = 0;
    Cell type = world[pos.x][pos.y];
    
    if (pos.x < 0 || pos.y < 0 || pos.x > COLUMNS || pos.y > ROWS)
        printf("\x1b[31mBUG: get_neighbors: out of range: %d, %d\x1b[m\n", pos.x, pos.y);

    for (int x = pos.x - 1; x < pos.x + 1; x++) {
		if (x < 0 || x >= COLUMNS)
			continue;

        for (int y = pos.y - 1; y < pos.y + 1; y++) {
            if (y < 0 || y >= ROWS)
			    continue;
            if (x == pos.x && y == pos.y)
                continue;
            if (type != TEAM_NONE)
                count += 1;
        }
    }

    return count;
}


void tick_cell(std::vector<std::vector<Cell>> &world, Vec2Int pos) {
    int count = get_neighbours(world, pos);
    
    switch (world[pos.x][pos.y]) {
        case TEAM_NONE:
            if (count == 3)
                world[pos.x][pos.y] = TEAM_BLUE;
            break;

        case TEAM_BLUE:
            printf("now %i | ", count);
            if (count != 2 && count != 3) {
                world[pos.x][pos.y] = TEAM_NONE;
            }
            break;
    }
}

int who_won(std::vector<std::vector<Cell>> &world) 
{
    int blue_count = 0;
    int red_count = 0;
    for (int x = 0; x < COLUMNS; x++) {
        for (int y = 0; y < ROWS; y++) {

            switch (world[x][y])
            {
            case TEAM_RED:
                red_count++;
                break;
            
            case TEAM_BLUE:
                blue_count++;
                break;
            }

        }   
    }
    if (blue_count > red_count) {
        return TEAM_BLUE;
    }
    else {
        return TEAM_RED;
    }
}