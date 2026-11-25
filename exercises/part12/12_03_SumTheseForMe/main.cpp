// Exercise 12.3: Sum These for Me
// See chapter 12 of the book for the assignment.

#include <array>
#include <iostream>
#include <print>
#include <span>
#include <string>

int sum(std::span<const int> numbers, int fromWhere, int toWhere, int smallest, int largest) {
    return 0;
}

int main() {
    std::array<int, 4> numbers = {3, -1, 8, 4};
    std::println("{}", sum(numbers, 0, 0, 0, 0));
    std::println("{}", sum(numbers, 0, 0, 0, 10));
    std::println("{}", sum(numbers, 0, 1, 0, 10));
    std::println("{}", sum(numbers, 0, 1, -10, 10));
    std::println("{}", sum(numbers, -1, 999, -10, 10));
}
