// Exercise 14.1: Shanghai
// See chapter 14 of the book for the assignment.

#include <utility>
#include <vector>
#include "chart.h"
#include "raylib.h"

int main() {
    InitWindow(640, 440, "Change this title");
    SetTargetFPS(60);
    // Store the rankings here and create a Chart

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        // Draw the axes and the line here

        EndDrawing();
    }

    CloseWindow();
}
