// Exercise 14.6: Smiley
// See chapter 14 of the book for the assignment.

#include "raylib.h"

int main() {
    InitWindow(640, 480, "Smiley");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        // Draw the smiley here with DrawRectangle

        EndDrawing();
    }

    CloseWindow();
}
