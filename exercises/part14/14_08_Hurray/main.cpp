// Exercise 14.8: Hurray
// See chapter 14 of the book for the assignment.

#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

int main() {
    InitWindow(300, 200, "Hurray");
    SetTargetFPS(60);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
    // Initialise the audio device and load the sound here

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        // Draw the button here, and play the sound when it is pressed

        EndDrawing();
    }
    // Unload the sound and close the audio device here

    CloseWindow();
}
