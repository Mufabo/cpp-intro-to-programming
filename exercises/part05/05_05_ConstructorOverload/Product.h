#pragma once

#include <format>
#include <string>

class Product {
public:
    Product(const std::string& name, const std::string& location, int weight)
        : name(name), location(location), weight(weight) {
    }

    // Add the three new constructors here

    std::string getName() const { return name; }
    int getWeight() const { return weight; }
    std::string getLocation() const { return location; }

    std::string toString() const {
        return std::format("{} ({} kg) can be found from the {}", name, weight, location);
    }

private:
    std::string name;
    std::string location;
    int weight;
};
