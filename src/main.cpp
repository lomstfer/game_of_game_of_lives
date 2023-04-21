#include <raylib.h>
#include <vector>
#include <utils.hpp>
#include <cell.hpp>
#include <iostream>

int main() {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGTH, "Game of Life");

    std::vector<std::vector<cell>> world;
    world.reserve(ROWS);
    for (size_t i = 0; i < world.size(); i++) {
        world[i].reserve(COLUMNS);
    }

    while (!WindowShouldClose()) {

        Vector2 mouse_pos_scaled = GetMousePosition() / (float)BLOCK_SIZE;

        BeginDrawing();
        for (size_t x = 0; x < COLUMNS; x++) {
            for (size_t y = 0; y < ROWS; y++) {
                if (world[x][y].alive) {
                    DrawRectangle(x * BLOCK_SIZE, y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, WHITE);
                }
            }
        }

        ClearBackground({50, 50, 50, 255});
        EndDrawing();
    }

    CloseWindow();
}