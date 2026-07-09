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

struct Tile { 
    TileState mainState { TileState::base };
    TileState displayState { TileState::base };
};

void callDrawFunction(TileState state, int startX, int startY) {
    using enum TileState;

    switch (state) {
    case base:
        // this case is here to make sure we do nothing (in case it is ever called)
        return;
    case bomb:
        // drawBomb(int startX, int startY); doesnt need to be called since bombs should be hidden
        DrawRectangle(startX * TILE_WIDTH, startY * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH, Color { ORANGE });
        return;
    case flag:
        drawFlag(startX, startY);
        return;
    default:
        drawNumber(static_cast<int>(state), startX, startY);
        return;
    }
}

int addBombsToGrid(std::array<std::array<Tile, SCREEN_WIDTH_TILES>, SCREEN_HEIGHT_TILES>& grid) {
    constexpr static double percentage { 0.2 };
    int bombCount { static_cast<int>(percentage * TILE_COUNT) };

    std::cout << bombCount << "\n";

    
    while (bombCount--) {

        int idx { Random::get(0, TILE_COUNT - bombCount) };

        for (auto& row : grid) {
            for (auto& tile : row) {
                if (tile.mainState != TileState::bomb) {
                    idx--;
                    if (idx < 1) {
                        tile.mainState = TileState::bomb;
                        goto end;
                    }
                }
            }
        }

    end:
    }

    return bombCount;
}

void addNumsToGrid(std::array<std::array<Tile, SCREEN_WIDTH_TILES>, SCREEN_HEIGHT_TILES>& grid) {

    for (int i { }; i < SCREEN_HEIGHT_TILES; ++i) {
        for (int j { }; j < SCREEN_WIDTH_TILES; ++j) {
            if (grid.data()[i].data()[j].mainState != TileState::base) continue;

            int counter { 0 };

            for (int a { i - 1}; a < i + 2; ++a) {
                for (int b { j - 1 }; b < j + 2; ++b) {
                    if (a < 0 || b < 0 || a >= SCREEN_HEIGHT_TILES || b >= SCREEN_WIDTH_TILES) continue;

                    if (grid.data()[a].data()[b].mainState == TileState::bomb) ++counter;
                }
            }

            grid.data()[i].data()[j].mainState = TileState { counter };
        }
    }

}

int main() {
    //state variables
    bool INPUTS_DISABLED { false };

    static std::array<std::array<Tile, SCREEN_WIDTH_TILES>, SCREEN_HEIGHT_TILES> grid {};

    addBombsToGrid(grid);

    addNumsToGrid(grid);

    InitWindow(SCREEN_WIDTH_TILES * TILE_WIDTH, SCREEN_HEIGHT_TILES * TILE_WIDTH, "My first window");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (INPUTS_DISABLED) goto drawing;
        if (IsMouseButtonPressed(0)) {
            int x { GetMouseX() / TILE_WIDTH };
            int y { GetMouseY() / TILE_WIDTH };

            if (grid[y][x].displayState == TileState::base) {
                grid[y][x].displayState = grid[y][x].mainState;
            }
        }

        if (IsMouseButtonPressed(1)) {
                int x { GetMouseX() / TILE_WIDTH };
                int y { GetMouseY() / TILE_WIDTH };

                if (grid[y][x].displayState == TileState::base) {
                    grid[y][x].displayState = TileState::flag;
                } else if (grid[y][x].displayState == TileState::flag) {
                    grid[y][x].displayState = TileState::base;
                }
        }

    drawing:

        BeginDrawing();

            ClearBackground(GRAY);

            for (int i { }; i < SCREEN_HEIGHT_TILES; ++i) {
                for (int j { }; j < SCREEN_WIDTH_TILES; ++j) {

                    if (grid[i][j].displayState != TileState::base) {
                        callDrawFunction(grid[i][j].displayState, j, i);
                    }
                }
            }

            for (int i { 1 }; i < SCREEN_HEIGHT_TILES; ++i) {
                DrawLine(0, TILE_WIDTH * i, i * TILE_WIDTH + TILE_WIDTH * SCREEN_HEIGHT_TILES, TILE_WIDTH * i, BLACK);
                DrawLine(TILE_WIDTH * i, 0, TILE_WIDTH * i, i * TILE_WIDTH + TILE_WIDTH * SCREEN_WIDTH_TILES, BLACK);
            }

            DrawFPS(5, 5);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

