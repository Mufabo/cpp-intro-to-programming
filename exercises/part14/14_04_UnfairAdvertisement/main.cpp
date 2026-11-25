// Exercise 14.4: Unfair Advertisement
// See chapter 14 of the book for the assignment.

#include <string>
#include <utility>
#include <vector>
#include "chart.h"
#include "raylib.h"

int main() {
    InitWindow(640, 440, "Internet speeds");
    SetTargetFPS(60);
    // Make this comparison fair. Explain your choices in a comment.
    std::vector<std::pair<std::string, double>> speeds = {
        {"NDA", 77.4}, {"Fastie", 77.2}, {"SuperNet", 77.1}, {"Meganet", 77.1}};
    Chart chart{Rectangle{80, 40, 520, 320}, 0, 5, 77.0, 77.5};

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Faster and Better!", 80, 10, 20, DARKBLUE);
        for (std::size_t i = 0; i < speeds.size(); i++) {
            drawBar(chart, static_cast<double>(i + 1), speeds[i].second, 0.6, i == 0 ? RED : GRAY);
            Vector2 label = toScreen(chart, static_cast<double>(i + 1), chart.yMin);
            DrawText(speeds[i].first.c_str(),
                     static_cast<int>(label.x) - MeasureText(speeds[i].first.c_str(), 16) / 2,
                     static_cast<int>(label.y) + 10, 16, DARKGRAY);
        }
        // the y axis without numbers: no reference point for the reader
        DrawLineEx(Vector2{80, 40}, Vector2{80, 360}, 2, DARKGRAY);
        DrawLineEx(Vector2{80, 360}, Vector2{600, 360}, 2, DARKGRAY);

        EndDrawing();
    }

    CloseWindow();
}
