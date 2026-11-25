// Exercise 14.2: Finnish Parties
// See chapter 14 of the book for the assignment.

#include <fstream>
#include <map>
#include <string>
#include <utility>
#include <vector>
#include "chart.h"
#include "raylib.h"

int main() {
    InitWindow(760, 480, "Relative support of the parties");
    SetTargetFPS(60);
    // Read partiesdata.tsv here (before the loop)

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        // Draw the chart and the legend here

        EndDrawing();
    }

    CloseWindow();
}
