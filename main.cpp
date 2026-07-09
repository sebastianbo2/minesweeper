#include "raylib.h"
#include "rlgl.h"

#include <iostream>
#include <array>

#include "random.hpp"

#include "constants.hpp"
#include "draw.hpp"

namespace GameState {
    bool INPUTS_DISABLED { false };
} // namespace GameState

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
    revealed,
    starting,
};

struct Tile { 
    TileState mainState { TileState::base };
    TileState displayState { TileState::base };
};

void revealBombs(std::array<std::array<Tile, SCREEN_WIDTH_TILES>, SCREEN_HEIGHT_TILES>& grid);

void callDrawFunction(TileState state, int startX, int startY) {
    using enum TileState;

    switch (state) {
    case base:
        // this case is here to make sure we do nothing (in case it is ever called)
        return;
    case bomb:
        // drawBomb(int startX, int startY); doesnt need to be called since bombs should be hidden
        return DrawRectangle(startX * TILE_WIDTH, startY * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH, ORANGE);
    case flag:
        return drawFlag(startX, startY);
    case starting:
        return DrawRectangle(startX * TILE_WIDTH, startY * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH, GREEN);
    default:
        DrawRectangle(startX * TILE_WIDTH, startY * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH, DARKGRAY);
        return drawNumber(static_cast<int>(state), startX, startY);
    }
}

void revealEmptyChain(std::array<std::array<Tile, SCREEN_WIDTH_TILES>, SCREEN_HEIGHT_TILES>& grid, int startX, int startY);

void clearTile(std::array<std::array<Tile, SCREEN_WIDTH_TILES>, SCREEN_HEIGHT_TILES>& grid, int startX, int startY) {
    if (grid[startY][startX].mainState == TileState::bomb) {
        GameState::INPUTS_DISABLED = true;
        revealBombs(grid);
    }

    grid[startY][startX].displayState = grid[startY][startX].mainState != TileState::base
                ? grid[startY][startX].mainState
                : (revealEmptyChain(grid, startX, startY), TileState::revealed);
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

int addNumsToGrid(std::array<std::array<Tile, SCREEN_WIDTH_TILES>, SCREEN_HEIGHT_TILES>& grid) {
    int count { 0 };

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

            if (counter == 0) count++;

            grid.data()[i].data()[j].mainState = TileState { counter };
        }
    }

    return count;
}

void revealBombs(std::array<std::array<Tile, SCREEN_WIDTH_TILES>, SCREEN_HEIGHT_TILES>& grid) {
    for (int y { }; y < SCREEN_HEIGHT_TILES; ++y) {
        for (int x { }; x < SCREEN_WIDTH_TILES; ++x) {
            std::cout << y << ", " << x << "\n";
            if (grid[y][x].mainState == TileState::bomb) {
                grid[y][x].displayState = TileState::bomb;
            }
        }
    }
}

void revealEmptyChain(std::array<std::array<Tile, SCREEN_WIDTH_TILES>, SCREEN_HEIGHT_TILES>& grid, int startX, int startY) {

    if (startX < 0 || startY < 0 || startX >= SCREEN_WIDTH_TILES || startY >= SCREEN_HEIGHT_TILES) return;

    if (grid[startY][startX].displayState == TileState::flag) {
        return;
    }

    if (grid[startY][startX].mainState != TileState::base) {
        grid[startY][startX].displayState = grid[startY][startX].mainState;
        return;
    }

    grid[startY][startX].displayState = TileState::revealed;

    bool test1 { false };
    bool test2 { false };
    bool test3 { false };
    bool test4 { false };

    if (startX > 0 && grid[startY][startX - 1].displayState != TileState::revealed) {
        revealEmptyChain(grid, startX - 1, startY);
        test1 = true;
    }

    if (startX < SCREEN_WIDTH_TILES - 1 && grid[startY][startX + 1].displayState != TileState::revealed) {
        revealEmptyChain(grid, startX + 1, startY);
        test2 = true;
    }

    if (startY > 0 && grid[startY - 1][startX].displayState != TileState::revealed) {
        revealEmptyChain(grid, startX, startY - 1);
        test3 = true;
    }

    if (startY < SCREEN_HEIGHT_TILES - 1 && grid[startY + 1][startX].displayState != TileState::revealed) {
        revealEmptyChain(grid, startX, startY + 1);
        test4 = true;
    }
    
    if (test1 && test3) revealEmptyChain(grid, startX - 1, startY - 1);
    if (test1 && test4) revealEmptyChain(grid, startX - 1, startY + 1);
    if (test2 && test3) revealEmptyChain(grid, startX + 1, startY - 1);
    if (test2 && test4) revealEmptyChain(grid, startX + 1, startY + 1);
}

void addStartingPointToGrid(std::array<std::array<Tile, SCREEN_WIDTH_TILES>, SCREEN_HEIGHT_TILES>& grid, int startingPoint) {

    for (auto& row : grid) {
        for (auto& tile : row) {
            if (tile.mainState != TileState::base) continue;
            if (startingPoint == 0) {
                tile.displayState = TileState::starting;
            }

            --startingPoint;
        } 
    }
}

void quickClear(std::array<std::array<Tile, SCREEN_WIDTH_TILES>, SCREEN_HEIGHT_TILES>& grid, int startX, int startY) {
    int counter { 0 };

    for (int a { startY - 1}; a < startY + 2; ++a) {
        for (int b { startX - 1 }; b < startX + 2; ++b) {
            if (a < 0 || b < 0 || a >= SCREEN_HEIGHT_TILES || b >= SCREEN_WIDTH_TILES) continue;

            if (grid.data()[a].data()[b].displayState == TileState::flag) ++counter;
        }
    }

    if (TileState { counter } == grid[startY][startX].mainState) {
        for (int a { startY - 1}; a < startY + 2; ++a) {
            for (int b { startX - 1 }; b < startX + 2; ++b) {
                if (a < 0 || b < 0 || a >= SCREEN_HEIGHT_TILES || b >= SCREEN_WIDTH_TILES) continue;
                if (grid[a][b].displayState == TileState::flag) continue;

                clearTile(grid, b, a);
            }
        }
    }
}

int main() {
    //state variables

    static std::array<std::array<Tile, SCREEN_WIDTH_TILES>, SCREEN_HEIGHT_TILES> grid {};

    addBombsToGrid(grid);

    const int startingPointCount { addNumsToGrid(grid) };
    const int startingPoint { Random::get(0, startingPointCount - 1) };

    addStartingPointToGrid(grid, startingPoint);

    InitWindow(SCREEN_WIDTH_TILES * TILE_WIDTH, SCREEN_HEIGHT_TILES * TILE_WIDTH, "My first window");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (GameState::INPUTS_DISABLED) goto drawing;
        if (IsMouseButtonPressed(0)) {
            int x { GetMouseX() / TILE_WIDTH };
            int y { GetMouseY() / TILE_WIDTH };

            if (grid[y][x].displayState == TileState::base or grid[y][x].displayState == TileState::starting) {
                clearTile(grid, x, y);
            } else if (grid[y][x].displayState >= TileState::one && grid[y][x].displayState <= TileState::nine) {
                quickClear(grid, x, y);
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

