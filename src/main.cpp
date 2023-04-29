#include <raylib.h>
#include <vector>
#include <utils.hpp>
#include <cell.hpp>
#include <iostream>

void draw_world(std::vector<std::vector<Cell>> &world);
void exit_now();

int main() {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGTH, "Game of Life");

    std::vector<std::vector<Cell>> world;
    world.reserve(ROWS);
    for (size_t i = 0; i < world.size(); i++) {
        world[i].reserve(COLUMNS);
    }

    for (size_t y = 0; y < ROWS; y++) {
        std::vector<Cell> temp_row;
        for (size_t x = 0; x < COLUMNS; x++) {
            temp_row.push_back(TEAM_NONE);
        }
        world.push_back(temp_row);
    }

    while (!IsKeyPressed(KEY_ENTER)) {
        if (WindowShouldClose())
            exit_now();

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            int x = GetMouseX() / BLOCK_SIZE;
            int y = GetMouseY() / BLOCK_SIZE;
            if ((x >= 0 && x < COLUMNS) && (y >= 0 && y < ROWS)) {
                set_cell(world, {x, y}, TEAM_BLUE);
            }
        }

        BeginDrawing();
            ClearBackground(COLOR_DEAD);
            draw_world(world);
        EndDrawing();
    }

    float tick_time = 0;

    while (true) {
        if (WindowShouldClose())
            exit_now();
        
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            int x = GetMouseX() / BLOCK_SIZE;
            int y = GetMouseY() / BLOCK_SIZE;
            if ((x >= 0 && x < COLUMNS) && (y >= 0 && y < ROWS)) {
                set_cell(world, {x, y}, TEAM_BLUE);
            }
        }

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
            for (int x = 0; x < COLUMNS; x++) {
                for (int y = 0; y < ROWS; y++) {
                    tick_cell(world, world_copy, {x, y});
                }
            }
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