// Exercise 14.9: Asteroids
// See chapter 14 of the book for the assignment.

#include <format>
#include <random>
#include <string>
#include <vector>
#include "raylib.h"
#include "raymath.h"

constexpr int WIDTH = 600;
constexpr int HEIGHT = 400;

// Return the number of the last part you have completed (1-4).
int partsCompleted() {
    return 0;
}

int main() {
    InitWindow(WIDTH, HEIGHT, "Asteroids!");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // 1. handle input
        // 2. update the game

        BeginDrawing();
        ClearBackground(BLACK);
        // 3. draw
        EndDrawing();
    }

    CloseWindow();
}
