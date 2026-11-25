#pragma once

#include <format>
#include <string>

class Person {
public:
    Person(const std::string& name, int height) : name(name), height(height) {
    }

    std::string getName() const { return name; }
    int getHeight() const { return height; }

    std::string toString() const {
        return std::format("{} ({} cm)", name, height);
    }

private:
    std::string name;
    int height;
};
