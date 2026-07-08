#include "raylib.h"

#include <iostream>
#include <array>

#include "constants.hpp"
#include "numbers.hpp"

int main() {

    InitWindow(SCREEN_WIDTH_TILES * TILE_WIDTH, SCREEN_HEIGHT_TILES * TILE_WIDTH, "My first window");

    std::array<std::array<bool, SCREEN_WIDTH_TILES>, SCREEN_HEIGHT_TILES> grid { };


    SetTargetFPS(30);

    while (!WindowShouldClose()) {
        BeginDrawing();

            ClearBackground(Color { GRAY });
            

            for (int i { }; i < SCREEN_HEIGHT_TILES; ++i) {
                for (int j { }; j < SCREEN_WIDTH_TILES; ++j) {
                    std::cout << i << ", " << j << "\n";

                    if (grid[i][j]) {
                        DrawRectangle(j * TILE_WIDTH, i * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH, Color { BLUE });
                    }
                    
                    DrawRectangleLines(j * TILE_WIDTH, i * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH, Color { BLACK });
                }
            }

            if (IsMouseButtonPressed(0)) {
                int y { GetMouseX() / TILE_WIDTH };
                int x { GetMouseY() / TILE_WIDTH };

                grid[x][y] = !grid[x][y];
            }

            // DrawRectangle(400, 200, 25, 25, Color { GRAY });

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

