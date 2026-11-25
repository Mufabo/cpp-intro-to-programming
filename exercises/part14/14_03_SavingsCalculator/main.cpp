// Exercise 14.3: Savings Calculator
// See chapter 14 of the book for the assignment.

#include <format>
#include <string>
#include <utility>
#include <vector>
#include "chart.h"
#include "layout.h"
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

int main() {
    InitWindow(760, 520, "Savings calculator");
    SetTargetFPS(60);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 16);
    float monthlySavings = 25;
    float yearlyInterest = 0;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        // Part 1: sliders and an empty chart
        // Parts 2 and 3: the savings lines

        EndDrawing();
    }

    CloseWindow();
}
