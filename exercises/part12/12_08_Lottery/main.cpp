// Exercise 12.8: Lottery
// See chapter 12 of the book for the assignment.

#include <iostream>
#include <print>
#include <string>
#include "LotteryRow.h"

int main() {
    LotteryRow row;
    std::println("Lottery numbers:");
    for (int number : row.numbers()) {
        std::print("{} ", number);
    }
    std::println("");
}
