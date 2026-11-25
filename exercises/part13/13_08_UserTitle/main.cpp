// Exercise 13.8: User Title
// See chapter 13 of the book for the assignment.

#include <iostream>
#include <print>
#include <string>
#include <vector>
#include "raylib.h"

int main(int argc, char* argv[]) {
    std::vector<std::string> args(argv + 1, argv + argc);
    std::string title = "Change me";

    // Use the first command-line argument as the title if there is one,
    // otherwise ask for the title in the terminal.

    InitWindow(480, 320, title.c_str());
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
    }
    CloseWindow();
}
