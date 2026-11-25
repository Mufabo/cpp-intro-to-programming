#pragma once

#include <string>
#include "Pet.h"

class Person {
public:
    Person(const std::string& name, const Pet& pet) : name(name), pet(pet) {
    }

    std::string toString() const {
        return name;
    }

private:
    std::string name;
    Pet pet;
};
