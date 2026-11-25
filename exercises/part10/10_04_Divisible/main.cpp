// Exercise 10.4: Divisible
// See chapter 10 of the book for the assignment.

#include <algorithm>
#include <functional>
#include <iostream>
#include <print>
#include <ranges>
#include <string>
#include <vector>

std::vector<int> divisible(const std::vector<int>& numbers) {
    return {};
}

int main() {
    std::vector<int> numbers = {3, 2, -17, -5, 7};
    for (int number : divisible(numbers)) {
        std::println("{}", number);
    }
}
