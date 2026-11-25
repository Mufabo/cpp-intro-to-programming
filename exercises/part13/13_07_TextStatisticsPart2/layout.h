#pragma once

// Small layout helpers for raygui programs. They compute rectangles, which is
// all a layout manager really does.

#include <vector>
#include "raylib.h"

struct BorderAreas {
    Rectangle top, bottom, left, right, center;
};

// The whole window as a rectangle, minus a margin on every side.
inline Rectangle windowArea(float margin = 10) {
    return Rectangle{margin, margin,
                     static_cast<float>(GetScreenWidth()) - 2 * margin,
                     static_cast<float>(GetScreenHeight()) - 2 * margin};
}

// Divides `area` into a border layout. `top` and `bottom` are heights,
// `left` and `right` are widths; the center gets the rest.
inline BorderAreas borderLayout(Rectangle area, float top, float bottom, float left, float right) {
    float middleHeight = area.height - top - bottom;
    float middleY = area.y + top;
    return BorderAreas{
        Rectangle{area.x, area.y, area.width, top},
        Rectangle{area.x, area.y + area.height - bottom, area.width, bottom},
        Rectangle{area.x, middleY, left, middleHeight},
        Rectangle{area.x + area.width - right, middleY, right, middleHeight},
        Rectangle{area.x + left, middleY, area.width - left - right, middleHeight},
    };
}

// Divides `area` into `count` equal parts side by side.
inline std::vector<Rectangle> hbox(Rectangle area, int count, float gap = 8) {
    std::vector<Rectangle> parts;
    float width = (area.width - gap * (count - 1)) / count;
    for (int i = 0; i < count; i++) {
        parts.push_back(Rectangle{area.x + i * (width + gap), area.y, width, area.height});
    }
    return parts;
}

// Divides `area` into `count` equal parts on top of each other.
inline std::vector<Rectangle> vbox(Rectangle area, int count, float gap = 8) {
    std::vector<Rectangle> parts;
    float height = (area.height - gap * (count - 1)) / count;
    for (int i = 0; i < count; i++) {
        parts.push_back(Rectangle{area.x, area.y + i * (height + gap), area.width, height});
    }
    return parts;
}

// The rectangle of cell (column, row) in a grid with the given number of columns and rows.
inline Rectangle gridCell(Rectangle area, int columns, int rows, int column, int row, float gap = 4) {
    float width = (area.width - gap * (columns - 1)) / columns;
    float height = (area.height - gap * (rows - 1)) / rows;
    return Rectangle{area.x + column * (width + gap), area.y + row * (height + gap), width, height};
}
