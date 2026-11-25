// Exercise 10.17: Sort Them Cards!
// See chapter 10 of the book for the assignment.

#include <algorithm>
#include <iostream>
#include <print>
#include <stdexcept>
#include <string>
#include <vector>
#include "Card.h"

int main() {
    Card first(2, Suit::Diamond);
    Card second(14, Suit::Spade);
    Card third(12, Suit::Heart);

    std::println("{}", first);
    std::println("{}", second);
    std::println("{}", third);
}
