#include "raylib.h"

#include <iostream>
#include <array>

#include "numbers.hpp"

int main() {

    constexpr int screenWidthScalar { 25 };
    constexpr int screenHeightScalar { 25 };
    constexpr int separator { 20 };

    InitWindow(screenWidthScalar * separator, screenWidthScalar * separator, "My first window");

    std::array<std::array<bool, screenWidthScalar>, screenHeightScalar> grid { };


    SetTargetFPS(30);

    while (!WindowShouldClose()) {
        BeginDrawing();

            ClearBackground(Color { WHITE });

            for (int i { }; i < screenHeightScalar; ++i) {
                for (int j { }; j < screenWidthScalar; ++j) {
                    std::cout << i << ", " << j << "\n";

                    if (grid[i][j]) {
                        DrawRectangle(j * separator, i * separator, separator, separator, Color { BLUE });
                    } else {
                        DrawRectangleLines(j * separator, i * separator, separator, separator, Color { LIGHTGRAY });
                    }
                }
            }

            if (IsMouseButtonPressed(0)) {
                int y { GetMouseX() / separator };
                int x { GetMouseY() / separator };

                grid[x][y] = !grid[x][y];
            }

            // DrawRectangle(400, 200, 25, 25, Color { GRAY });

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

