// Exercise 7.4: Ready-made Sorting Algorithms
// See chapter 7 of the book for the assignment.

#include <algorithm>
#include <array>
#include <iostream>
#include <print>
#include <string>
#include <vector>

void sort(std::array<int, 5>& numbers) {
}

void sort(std::array<std::string, 3>& words) {
}

void sortIntegers(std::vector<int>& integers) {
}

void sortStrings(std::vector<std::string>& strings) {
}

int main() {
    std::array<int, 5> numbers = {3, 1, 5, 99, 3};
    sort(numbers);
    std::println("{}", numbers);

    std::array<std::string, 3> words = {"pear", "apple", "fig"};
    sort(words);
    std::println("{}", words);
}
