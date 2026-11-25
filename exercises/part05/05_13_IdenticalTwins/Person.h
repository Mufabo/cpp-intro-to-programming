#pragma once

#include <string>
#include "SimpleDate.h"

class Person {
public:
    Person(const std::string& name, const SimpleDate& birthday, int height, int weight)
        : name(name), birthday(birthday), height(height), weight(weight) {
    }

    // Add operator== here

private:
    std::string name;
    SimpleDate birthday;
    int height;
    int weight;
};
