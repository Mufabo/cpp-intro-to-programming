#pragma once

#include "MagicSquare.h"

class MagicSquareFactory {
public:
    MagicSquare createMagicSquare(int size) const {
        MagicSquare square(size);
        // Part 4: implement the Siamese method here
        return square;
    }
};
