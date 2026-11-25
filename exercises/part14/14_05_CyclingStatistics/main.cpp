// Exercise 14.5: Cycling Statistics
// See chapter 14 of the book for the assignment.
// This program shows the data as a line chart. Change it to show a bar chart.

#include <algorithm>
#include <string>
#include <utility>
#include <vector>
#include "CyclingStatistics.h"
#include "chart.h"
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

int main() {
    InitWindow(900, 520, "Cycling statistics");
    SetTargetFPS(60);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 16);

    CyclingStatistics statistics("cycling-monthly.csv");
    std::vector<std::string> stations = statistics.stations();
    std::string dropdownText;
    for (std::size_t i = 0; i < stations.size(); i++) {
        dropdownText += (i == 0 ? "" : ";") + stations[i];
    }
    int chosen = 0;
    bool dropdownOpen = false;

    while (!WindowShouldClose()) {
        std::map<std::string, int> values = statistics.monthlyCyclists(stations[chosen]);
        int largest = 1;
        for (const auto& [month, count] : values) {
            largest = std::max(largest, count);
        }
        Chart chart{Rectangle{90, 70, 780, 380}, 0, static_cast<double>(values.size() + 1), 0,
                    static_cast<double>(largest)};

        BeginDrawing();
        ClearBackground(RAYWHITE);

        std::vector<std::pair<double, double>> points;
        int index = 1;
        for (const auto& [month, count] : values) {
            points.emplace_back(index, count);
            index++;
        }
        drawAxes(chart, 3, largest / 5.0, "Month (from 2014/01)", "Cyclists");
        drawLine(chart, points, DARKBLUE);

        // draw the dropdown last, so that its list appears on top of the chart
        if (GuiDropdownBox(Rectangle{90, 15, 300, 30}, dropdownText.c_str(), &chosen, dropdownOpen)) {
            dropdownOpen = !dropdownOpen;
        }
        EndDrawing();
    }
    CloseWindow();
}
