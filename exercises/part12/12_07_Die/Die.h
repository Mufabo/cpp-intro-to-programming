#pragma once

#include <random>

class Die {
public:
    Die(int numberOfFaces) : engine(std::random_device{}()) {
        // Initialise numberOfFaces here
    }

    int throwDie() {
        // generate a random number between one and the number of faces, and return it
        return 0;
    }

private:
    std::mt19937 engine;
    int numberOfFaces = 0;
};
