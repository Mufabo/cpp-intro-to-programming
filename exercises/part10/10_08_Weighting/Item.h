#pragma once

#include <format>
#include <string>

class Item {
public:
    Item(const std::string& name, int weight) : name(name), weight(weight) {
    }

    std::string getName() const { return name; }
    int getWeight() const { return weight; }

    std::string toString() const {
        return std::format("{} ({} kg)", name, weight);
    }

private:
    std::string name;
    int weight;
};
