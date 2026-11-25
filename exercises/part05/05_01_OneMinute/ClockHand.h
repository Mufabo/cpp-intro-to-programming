#pragma once

#include <format>
#include <string>

class ClockHand {
public:
    ClockHand(int limit) : value(0), limit(limit) {
    }

    void advance() {
        value = value + 1;
        if (value >= limit) {
            value = 0;
        }
    }

    int getValue() const {
        return value;
    }

    std::string toString() const {
        return std::format("{:02}", value);
    }

private:
    int value;
    int limit;
};
