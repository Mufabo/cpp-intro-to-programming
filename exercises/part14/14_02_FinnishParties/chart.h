#pragma once

// A tiny charting helper for raylib: axes, lines, bars and a legend.

#include <cmath>
#include <format>
#include <string>
#include <utility>
#include <vector>
#include "raylib.h"

struct Chart {
    Rectangle plot;                 // where the plot area is on the screen
    double xMin, xMax, yMin, yMax;  // the visible data range
};

inline Vector2 toScreen(const Chart& chart, double x, double y) {
    float sx = chart.plot.x + static_cast<float>((x - chart.xMin) / (chart.xMax - chart.xMin)) * chart.plot.width;
    float sy = chart.plot.y + chart.plot.height
               - static_cast<float>((y - chart.yMin) / (chart.yMax - chart.yMin)) * chart.plot.height;
    return Vector2{sx, sy};
}

inline std::string formatTick(double value) {
    if (std::abs(value - std::round(value)) < 1e-9) {
        return std::format("{}", static_cast<long long>(std::round(value)));
    }
    return std::format("{:.1f}", value);
}

// Axes with tick marks every xStep / yStep data units.
inline void drawAxes(const Chart& chart, double xStep, double yStep,
                     const std::string& xLabel, const std::string& yLabel) {
    const int fontSize = 14;
    Rectangle p = chart.plot;
    DrawLineEx(Vector2{p.x, p.y + p.height}, Vector2{p.x + p.width, p.y + p.height}, 2, DARKGRAY);
    DrawLineEx(Vector2{p.x, p.y}, Vector2{p.x, p.y + p.height}, 2, DARKGRAY);

    for (double x = chart.xMin; x <= chart.xMax + 1e-9; x += xStep) {
        Vector2 s = toScreen(chart, x, chart.yMin);
        DrawLineV(s, Vector2{s.x, s.y + 5}, DARKGRAY);
        std::string text = formatTick(x);
        DrawText(text.c_str(), static_cast<int>(s.x) - MeasureText(text.c_str(), fontSize) / 2,
                 static_cast<int>(s.y) + 8, fontSize, DARKGRAY);
    }
    for (double y = chart.yMin; y <= chart.yMax + 1e-9; y += yStep) {
        Vector2 s = toScreen(chart, chart.xMin, y);
        DrawLineV(s, Vector2{s.x - 5, s.y}, DARKGRAY);
        DrawLineV(s, Vector2{p.x + p.width, s.y}, Fade(LIGHTGRAY, 0.6f));
        std::string text = formatTick(y);
        DrawText(text.c_str(), static_cast<int>(s.x) - 8 - MeasureText(text.c_str(), fontSize),
                 static_cast<int>(s.y) - fontSize / 2, fontSize, DARKGRAY);
    }
    DrawText(xLabel.c_str(), static_cast<int>(p.x + p.width / 2) - MeasureText(xLabel.c_str(), fontSize) / 2,
             static_cast<int>(p.y + p.height) + 26, fontSize, BLACK);
    DrawText(yLabel.c_str(), static_cast<int>(p.x), static_cast<int>(p.y) - fontSize - 6, fontSize, BLACK);
}

// A line through the points, in order.
inline void drawLine(const Chart& chart, const std::vector<std::pair<double, double>>& points, Color color) {
    for (std::size_t i = 0; i + 1 < points.size(); i++) {
        DrawLineEx(toScreen(chart, points[i].first, points[i].second),
                   toScreen(chart, points[i + 1].first, points[i + 1].second), 2, color);
    }
    for (const auto& [x, y] : points) {
        DrawCircleV(toScreen(chart, x, y), 3, color);
    }
}

// A bar from 0 (or yMin, if that is larger) up to `value`, centred on x, `width` data units wide.
inline void drawBar(const Chart& chart, double x, double value, double width, Color color) {
    double base = chart.yMin > 0 ? chart.yMin : 0;
    Vector2 topLeft = toScreen(chart, x - width / 2, value);
    Vector2 bottomRight = toScreen(chart, x + width / 2, base);
    DrawRectangleRec(Rectangle{topLeft.x, topLeft.y, bottomRight.x - topLeft.x, bottomRight.y - topLeft.y}, color);
}

// A legend: coloured boxes with names, one per line, starting at `position`.
inline void drawLegend(Vector2 position, const std::vector<std::pair<std::string, Color>>& entries) {
    const int fontSize = 14;
    for (std::size_t i = 0; i < entries.size(); i++) {
        int y = static_cast<int>(position.y) + static_cast<int>(i) * (fontSize + 6);
        DrawRectangle(static_cast<int>(position.x), y, fontSize, fontSize, entries[i].second);
        DrawText(entries[i].first.c_str(), static_cast<int>(position.x) + fontSize + 6, y, fontSize, BLACK);
    }
}
