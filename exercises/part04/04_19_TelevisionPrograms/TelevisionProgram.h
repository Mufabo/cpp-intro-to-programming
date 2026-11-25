#pragma once

#include <format>
#include <string>

class TelevisionProgram {
public:
    TelevisionProgram(const std::string& name, int duration)
        : name(name), duration(duration) {
    }

    std::string getName() const { return name; }
    int getDuration() const { return duration; }

    std::string toString() const {
        return std::format("{}, {} minutes", name, duration);
    }

private:
    std::string name;
    int duration;
};
