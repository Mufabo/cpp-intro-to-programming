// Exercise 10.11: Wage Order
// See chapter 10 of the book for the assignment.

#include <algorithm>
#include <iostream>
#include <print>
#include <string>
#include <vector>
#include "Human.h"

int main() {
    std::vector<Human> humans = {{"Matti", 150000}, {"Merja", 500}, {"Pertti", 80}, {"Ada", 4000}};
    // Uncomment when the ordering exists:
    // std::ranges::sort(humans);
    for (const Human& human : humans) {
        std::println("{}", human.toString());
    }
}
