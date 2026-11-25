// Exercise 12.10: Magic Square
// See chapter 12 of the book for the assignment.

#include <iostream>
#include <print>
#include <string>
#include "MagicSquare.h"
#include "MagicSquareFactory.h"

int main() {
    MagicSquare square(3);
    int values[3][3] = {{8, 1, 6}, {3, 5, 7}, {4, 9, 2}};
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            square.placeValue(x, y, values[y][x]);
        }
    }
    std::println("{}", square.sumsOfRows());
    std::println("Magic square? {}", square.isMagicSquare());

    MagicSquareFactory factory;
    std::print("{}", factory.createMagicSquare(3).toString());
}
