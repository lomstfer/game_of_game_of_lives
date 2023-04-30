#include <vector>
#include <iostream>

#include <raylib.h>

#include <utils.hpp>
#include <cell.hpp>
#include <state_machine.hpp>

void draw_world(std::vector<std::vector<Cell>> &world);
void exit_now();

int main() {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGTH, "Game of Life");

    std::vector<std::vector<Cell>> world;
    world.reserve(ROWS);
    for (size_t y = 0; y < ROWS; y++) {
        std::vector<Cell> temp_row;
        world[y].reserve(COLUMNS);
        for (size_t x = 0; x < COLUMNS; x++) {
            temp_row.push_back(TEAM_NONE);
        }
        world.push_back(temp_row);
    }



    while (true) {
        if (WindowShouldClose())
            exit_now();
        
        if (!IsKeyPressed(KEY_ENTER)) {
			cells_placed = 0;
			switch (state)
			{
			case BLUE_TURN:
				state = RED_TURN;
				break;
			
			case RED_TURN:
				state = SIMULATING;
				break;
			}
        }

        switch (state)
        {
        case BLUE_TURN:
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                int x = GetMouseX() / BLOCK_SIZE;
                int y = GetMouseY() / BLOCK_SIZE;
                if ((x >= 0 && x < COLUMNS) && (y >= 0 && y < ROWS)) {
                    set_cell(world, {x, y}, TEAM_BLUE);
                }
            }
            break;
        
        case RED_TURN:
			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                int x = GetMouseX() / BLOCK_SIZE;
                int y = GetMouseY() / BLOCK_SIZE;
                if ((x >= 0 && x < COLUMNS) && (y >= 0 && y < ROWS)) {
                    set_cell(world, {x, y}, TEAM_RED);
                }
            }
            break;
        
        case SIMULATING:
			std::vector<std::vector<Cell>> world_copy;
			for (size_t y = 0; y < ROWS; y++) {
				std::vector<Cell> temp_row;
				for (size_t x = 0; x < COLUMNS; x++) {
					temp_row.push_back(world[y][x]);
				}
				world_copy.push_back(temp_row);
			}

			tick_time += GetFrameTime();
			if (tick_time > TICKS_PER_SECOND) {
				tick_time = 0;
				tick_count++;

				if (tick_count > TICKS_PER_TURN)
					state = BLUE_TURN;

				for (int x = 0; x < COLUMNS; x++) {
					for (int y = 0; y < ROWS; y++) {
						tick_cell(world, world_copy, {x, y});
					}
				}
			}
            break;

        }


        
		BeginDrawing();
		ClearBackground(COLOR_DEAD);
		draw_world(world);
		EndDrawing();
    }

    exit_now();
}

void draw_world(std::vector<std::vector<Cell>> &world) {
    for (int x = 0; x < COLUMNS; x++) {
        for (int y = 0; y < ROWS; y++) {
            DrawRectangleLines(x * BLOCK_SIZE, y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, {40,40,40,255});

            switch (get_cell(world, {x, y})) {
            case TEAM_RED:
                DrawRectangle(x * BLOCK_SIZE, y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, RED);
                break;
            case TEAM_BLUE:
                DrawRectangle(x * BLOCK_SIZE, y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, BLUE);
                break;
            }
        }
    }
}

void exit_now() {
    CloseWindow();
    exit(0);
}