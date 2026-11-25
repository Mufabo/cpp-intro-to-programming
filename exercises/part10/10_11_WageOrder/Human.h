#pragma once

#include <compare>
#include <format>
#include <string>

class Human {
public:
    Human(const std::string& name, int wage) : name(name), wage(wage) {
    }

    std::string getName() const { return name; }
    int getWage() const { return wage; }

    // Define operator<=> and operator== here

    std::string toString() const {
        return std::format("{} {}", name, wage);
    }

private:
    std::string name;
    int wage;
};
