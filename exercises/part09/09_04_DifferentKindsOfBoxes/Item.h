#pragma once

#include <format>
#include <string>

class Item {
public:
    Item(const std::string& name, int weight) : name(name), weight(weight) {
    }

    Item(const std::string& name) : Item(name, 0) {
    }

    std::string getName() const { return name; }
    int getWeight() const { return weight; }

    // Part 1: add operator== here (items with the same name are equal)

    std::string toString() const {
        return std::format("{} ({} kg)", name, weight);
    }

private:
    std::string name;
    int weight;
};
