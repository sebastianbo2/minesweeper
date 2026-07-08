#include <raylib.h>

#include "numbers.hpp"

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