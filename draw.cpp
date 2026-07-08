#include <raylib.h>

#include <array>

#include "draw.hpp"

struct DrawingData {
    int offset { };
    int length { };
};

void drawFlag(int startX, int startY) {
    constexpr static int baseFlagOffset { 13 };
    constexpr static int baseYOffset { 6 };

    /* the flag was drawn by me using a previous version of the board for this game
     so i just copied what pixels were on in here */
    constexpr static std::array<DrawingData, 18> flagLineData {{
        { baseFlagOffset, 2 },
        { baseFlagOffset, 2 },
        { baseFlagOffset, 10 },
        { baseFlagOffset, 9 },
        { baseFlagOffset, 8 },
        { baseFlagOffset, 7 },
        { baseFlagOffset, 7 },
        { baseFlagOffset, 8 },
        { baseFlagOffset, 9 },
        { baseFlagOffset, 10 },
        { baseFlagOffset, 2 },
        { baseFlagOffset, 2 },
        { baseFlagOffset, 2 },
        { baseFlagOffset, 2 },
        { baseFlagOffset, 2 },
        { baseFlagOffset - 1, 4 },
        { baseFlagOffset - 2, 6 },
        { baseFlagOffset - 3, 8 },
    }};

    for (int i { }; i < std::ssize(flagLineData); ++i) {
        DrawLine(
            startX * TILE_WIDTH + flagLineData.data()[i].offset,
            startY * TILE_WIDTH + baseYOffset + i,
            startX * TILE_WIDTH + flagLineData.data()[i].offset + flagLineData.data()[i].length - 1,
            startY * TILE_WIDTH + baseYOffset + i,
            Color { RED });
    }
}

void drawOne(int startX, int startY) {
    DrawText("1", (startX * TILE_WIDTH) + NUMBER_OFFSET, (startY * TILE_WIDTH) + 3, 28, Color { SKYBLUE });
}

void drawTwo(int startX, int startY) {
    DrawText("2", (startX * TILE_WIDTH) + NUMBER_OFFSET, (startY * TILE_WIDTH) + 3, 28, Color { LIME });
}

void drawThree(int startX, int startY) {
    DrawText("3", (startX * TILE_WIDTH) + NUMBER_OFFSET, (startY * TILE_WIDTH) + 3, 28, Color { MAROON });
}

void drawFour(int startX, int startY) {
    DrawText("4", (startX * TILE_WIDTH) + NUMBER_OFFSET, (startY * TILE_WIDTH) + 3, 28, Color { PURPLE });
}

void drawFive(int startX, int startY) {
    DrawText("5", (startX * TILE_WIDTH) + NUMBER_OFFSET, (startY * TILE_WIDTH) + 3, 28, Color { YELLOW });
}

void drawSix(int startX, int startY) {
    DrawText("6", (startX * TILE_WIDTH) + NUMBER_OFFSET, (startY * TILE_WIDTH) + 3, 28, Color { BLUE });
}

void drawSeven(int startX, int startY) {
    DrawText("7", (startX * TILE_WIDTH) + NUMBER_OFFSET, (startY * TILE_WIDTH) + 3, 28, Color { LIGHTGRAY });
}

void drawEight(int startX, int startY) {
    DrawText("8", (startX * TILE_WIDTH) + NUMBER_OFFSET, (startY * TILE_WIDTH) + 3, 28, Color { BEIGE });
}

void drawNine(int startX, int startY) {
    DrawText("9", (startX * TILE_WIDTH) + NUMBER_OFFSET, (startY * TILE_WIDTH) + 3, 28, Color { RED });
}