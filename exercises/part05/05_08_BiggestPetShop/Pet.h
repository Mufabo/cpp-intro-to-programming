#pragma once

#include <string>

class Pet {
public:
    Pet(const std::string& name, const std::string& breed) : name(name), breed(breed) {
    }

    std::string getName() const { return name; }
    std::string getBreed() const { return breed; }

private:
    std::string name;
    std::string breed;
};
