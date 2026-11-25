#pragma once

#include <compare>
#include <string>

class Student {
public:
    Student(const std::string& name) : name(name) {
    }

    std::string getName() const { return name; }

    // Define the ordering here

    std::string toString() const {
        return name;
    }

private:
    std::string name;
};
