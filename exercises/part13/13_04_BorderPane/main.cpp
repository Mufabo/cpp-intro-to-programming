// Exercise 13.4: Border Layout
// See chapter 13 of the book for the assignment.

#include <string>
#include "layout.h"
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(480, 320, "Border layout");
    SetTargetFPS(60);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw your user interface here

        EndDrawing();
    }

    CloseWindow();
}
