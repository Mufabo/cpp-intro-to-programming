#pragma once

#include <string>

class Movable {
public:
    virtual ~Movable() = default;
    virtual void move(int dx, int dy) = 0;
};
