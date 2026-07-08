#include "raylib.h"

#include <iostream>
#include <array>

#include "constants.hpp"
#include "draw.hpp"

enum class TileState : int {
    base,
    one,
    two,
    three,
    four,
    five,
    six,
    seven,
    eight,
    nine,
    bomb,
    flag,
};

void callDrawFunction(TileState state, int startX, int startY) {
    using enum TileState;

    switch (state) {
    case base:
        return;
    case bomb:
        return;
    case flag:
        drawFlag(startX, startY);
        return;
    default:
        // drawNumber(static_cast<int>(state), startX, startY);
        return;
    }
}

int main() {

    InitWindow(SCREEN_WIDTH_TILES * TILE_WIDTH, SCREEN_HEIGHT_TILES * TILE_WIDTH, "My first window");

    std::array<std::array<TileState, SCREEN_WIDTH_TILES>, SCREEN_HEIGHT_TILES> grid {{ }};


    SetTargetFPS(30);

    while (!WindowShouldClose()) {
        BeginDrawing();

            ClearBackground(Color { GRAY });
            

            for (int i { }; i < SCREEN_HEIGHT_TILES; ++i) {
                for (int j { }; j < SCREEN_WIDTH_TILES; ++j) {
                    if (grid[j][i] != TileState::base) {
                        callDrawFunction(grid[j][i], i, j);
                    }
                    
                    DrawRectangleLines(j * TILE_WIDTH, i * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH, Color { BLACK });
                }
            }

            if (IsMouseButtonPressed(1)) {
                int x { GetMouseX() / TILE_WIDTH };
                int y { GetMouseY() / TILE_WIDTH };

                if (grid[y][x] == TileState::base) {
                    grid[y][x] = TileState::flag;
                } else if (grid[y][x] == TileState::flag) {
                    grid[y][x] = TileState::base;
                } else {
                    throw std::runtime_error("Invalid case with flag");
                }
            }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

