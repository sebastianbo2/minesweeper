#include "raylib.h"
#include "rlgl.h"

#include <iostream>
#include <array>

#include "random.hpp"

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
        // this case is here to make sure we do nothing (in case it is ever called)
        return;
    case bomb:
        // drawBomb(int startX, int startY); doesnt need to be called since bombs should be hidden
        // drawNine(startX, startY);
        DrawRectangle(startX * TILE_WIDTH, startY * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH, Color { ORANGE });
        return;
    case flag:
        drawFlag(startX, startY);
        return;
    default:
        // drawNumber(static_cast<int>(state), startX, startY);
        return;
    }
}

int addBombsToGrid(std::array<std::array<TileState, SCREEN_WIDTH_TILES>, SCREEN_HEIGHT_TILES>& grid) {
    constexpr static double percentage { 0.2 };
    int bombCount { static_cast<int>(percentage * TILE_COUNT) };

    std::cout << bombCount << "\n";

    
    while (bombCount--) {

        int idx { Random::get(0, TILE_COUNT - bombCount) };

        for (auto& row : grid) {
            for (auto& tile : row) {
                if (tile != TileState::bomb) {
                    idx--;
                    if (idx < 1) {
                        tile = TileState::bomb;
                        goto end;
                    }
                }
            }
        }

        end:

    }

    return bombCount;
}

int main() {
    static std::array<std::array<TileState, SCREEN_WIDTH_TILES>, SCREEN_HEIGHT_TILES> grid {};

    for (auto i { 0uz }; i < grid.size(); ++i) {
        for (auto j { 0uz }; j < grid[i].size(); ++j) {
            grid[i][j] = TileState::base;
        }
    }

    addBombsToGrid(grid);

    InitWindow(SCREEN_WIDTH_TILES * TILE_WIDTH, SCREEN_HEIGHT_TILES * TILE_WIDTH, "My first window");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (IsMouseButtonPressed(1)) {
                int x { GetMouseX() / TILE_WIDTH };
                int y { GetMouseY() / TILE_WIDTH };

                if (grid[y][x] == TileState::base) {
                    grid[y][x] = TileState::flag;
                } else if (grid[y][x] == TileState::flag) {
                    grid[y][x] = TileState::base;
                }
            }

        BeginDrawing();

            ClearBackground(GRAY);

            DrawFPS(5, 5);
            

            for (int i { }; i < SCREEN_HEIGHT_TILES; ++i) {
                for (int j { }; j < SCREEN_WIDTH_TILES; ++j) {
                    DrawRectangle(i * TILE_WIDTH, j * TILE_WIDTH, TILE_WIDTH - 1, TILE_WIDTH - 1, BLACK);

                    if (grid[i][j] != TileState::base) {
                        callDrawFunction(grid[i][j], j, i);
                    }
                    
                    // DrawRectangleLines(i * TILE_WIDTH, j * TILE_WIDTH, TILE_WIDTH - 1, TILE_WIDTH - 1, BLACK);
                }
            }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

