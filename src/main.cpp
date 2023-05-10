#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <raylib.h>

#include <cell.hpp>
#include <state_machine.hpp>
#include <utils.hpp>

/// Description:        A function checks for input and modifies data to make the program work.
/// Argument 1:         std::vector<std::vector<Cell>>, a 2d array representing the world.
/// Argument 2:         int, the number of cells team blue has left to place out.
/// Argument 3:         int, the number of cells team red has left to place out.
/// Argument 4:         float, bigger means faster game and smaller means slower game.
void game_loop(std::vector<std::vector<Cell>>& world, int& blue_inventory, int& red_inventory, float& ticks_per_second_multiplier);

/// Description:        A function that draws all of text.
/// Argument 1:         std::vector<std::vector<Cell>>, a 2d array representing the world.
/// Argument 2:         int, the number of cells team blue has left to place out.
/// Argument 3:         int, the number of cells team red has left to place out.
/// Example:         	draw_world( 
///								{ {TEAM_NONE, TEAM_BLUE, TEAM_NONE},
///								{TEAM_NONE, TEAM_RED, TEAM_NONE},
///								{TEAM_NONE, TEAM_BLUE, TEAM_NONE} },
///								{1, 1}
///						#===> draws all the text to the window
void draw_info(std::vector<std::vector<Cell>>& world, int blue_inventory, int red_inventory);

/// Description:        A function that draws all of the cells and the grid.
/// Argument 1:         std::vector<std::vector<Cell>>, a 2d array representing the world.
/// Example:         	draw_world( 
///								{ {TEAM_NONE, TEAM_BLUE, TEAM_NONE},
///								{TEAM_NONE, TEAM_RED, TEAM_NONE},
///								{TEAM_NONE, TEAM_BLUE, TEAM_NONE} },
///								{1, 1}
///						#===> draws all the active cells to the window with their color and the other cells black
void draw_world(std::vector<std::vector<Cell>>& world);

int main(void)
{
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGTH, "Game of Game of Life");

	std::vector<std::vector<Cell>> world;
	world.reserve(ROWS);
	for (size_t y = 0; y < ROWS; y++) {
		std::vector<Cell> temp_row;
		for (size_t x = 0; x < COLUMNS; x++) {
			temp_row.push_back(TEAM_NONE);
		}
		world.push_back(temp_row);
	}

	int blue_inventory = CELLS_PER_TURN;
	int red_inventory = 0;

	float ticks_per_second_multiplier = 1;

	while (!WindowShouldClose()) {
		game_loop(world, blue_inventory, red_inventory, ticks_per_second_multiplier);

		BeginDrawing();
		
		ClearBackground(COLOR_DEAD);
		draw_world(world);
		draw_info(world, blue_inventory, red_inventory);

		EndDrawing();
	}

	CloseWindow();
}

void game_loop(std::vector<std::vector<Cell>>& world, int& blue_inventory, int& red_inventory, float& ticks_per_second_multiplier)
{
	if (IsKeyPressed(KEY_ENTER)) {
		cells_placed = 0;
		switch (state) {
		case BLUE_TURN:
			state = RED_TURN;
			blue_inventory = 0;
			red_inventory += CELLS_PER_TURN;
			break;
		case RED_TURN:
			state = SIMULATING;
			red_inventory = 0;
			blue_inventory += CELLS_PER_TURN;
			break;
		}
	}

	switch (state) {
	case BLUE_TURN:
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			int x = GetMouseX() / BLOCK_SIZE;
			int y = GetMouseY() / BLOCK_SIZE;
			if ((x >= 0 && x < COLUMNS) &&
				(y >= 0 && y < ROWS)) {
				Cell prev_type =
					get_cell(world, {x, y});
				if (prev_type == TEAM_NONE &&
					blue_inventory > 0) {
					set_cell(world, {x, y},
							TEAM_BLUE);
					blue_inventory--;
					break;
				}

				if (prev_type == TEAM_BLUE) {
					set_cell(world, {x, y},
							TEAM_NONE);
					blue_inventory++;
					break;
				}
			}
		}
		break;

	case RED_TURN:
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			int x = GetMouseX() / BLOCK_SIZE;
			int y = GetMouseY() / BLOCK_SIZE;
			if ((x >= 0 && x < COLUMNS) &&
				(y >= 0 && y < ROWS)) {
				Cell prev_type =
					get_cell(world, {x, y});

				if (prev_type == TEAM_NONE &&
					red_inventory > 0) {
					set_cell(world, {x, y},
							TEAM_RED);
					red_inventory--;
					break;
				}

				if (prev_type == TEAM_RED) {
					set_cell(world, {x, y},
							TEAM_NONE);
					red_inventory++;
					break;
				}
			}
		}
		break;

	case SIMULATING:
		if (IsKeyDown(KEY_UP)) {
			if (ticks_per_second_multiplier > 0)
				ticks_per_second_multiplier -= GetFrameTime() * 0.2f;
			else
				ticks_per_second_multiplier = 0;
		}
		if (IsKeyDown(KEY_DOWN)) {
			ticks_per_second_multiplier += GetFrameTime() * 0.2f;
		}

		std::vector<std::vector<Cell>> world_copy(world);

		tick_time += GetFrameTime();
		if (tick_time > TICKS_PER_SECOND * ticks_per_second_multiplier) {
			tick_time = 0;
			tick_count++;

			for (int x = 0; x < COLUMNS; x++) {
				for (int y = 0; y < ROWS; y++) {
					tick_cell(world, world_copy,
							{x, y});
				}
			}
		}
		break;
	}
	return;
}

void draw_info(std::vector<std::vector<Cell>>& world, int blue_inventory, int red_inventory) {
	std::stringstream ss_cells;
	std::stringstream ss_balance;

	switch (state) {
	case BLUE_TURN:
		ss_cells << "Cells left: " << blue_inventory;
		DrawText("Blues turn...", 5, 5, 20, WHITE);
		break;

	case RED_TURN:
		ss_cells << "Cells left: " << red_inventory;
		DrawText("Reds turn...", 5, 5, 20, WHITE);
		break;

	case SIMULATING:
		DrawText("Simulating...", 5, 5, 20, WHITE);
		break;
	}

	std::string cells_left_str = ss_cells.str();
	DrawText(cells_left_str.c_str(), 5, 40, 20, WHITE);

	CellCount count = count_cells(world);
	ss_balance << count.blues << " blues - " << count.reds
			<< " reds";
	std::string balance_str = ss_balance.str();
	DrawText(balance_str.c_str(), 5, 75, 20, WHITE);
	return;
}

void draw_world(std::vector<std::vector<Cell>>& world)
{
	for (int x = 0; x < COLUMNS; x++) {
		for (int y = 0; y < ROWS; y++) {
			DrawRectangleLines(x * BLOCK_SIZE, y * BLOCK_SIZE,
				BLOCK_SIZE, BLOCK_SIZE,
				{40, 40, 40, 255});

			switch (get_cell(world, {x, y})) {
			case TEAM_RED:
				DrawRectangle(x * BLOCK_SIZE, y * BLOCK_SIZE,
					BLOCK_SIZE, BLOCK_SIZE, RED);
				break;
			case TEAM_BLUE:
				DrawRectangle(x * BLOCK_SIZE, y * BLOCK_SIZE,
					BLOCK_SIZE, BLOCK_SIZE, BLUE);
				break;
			}
		}
	}
	return;
}
