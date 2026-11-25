// Exercise 10.3: Positive Numbers
// See chapter 10 of the book for the assignment.

#include <algorithm>
#include <functional>
#include <iostream>
#include <print>
#include <ranges>
#include <string>
#include <vector>

std::vector<int> positive(const std::vector<int>& numbers) {
    // use std::views::filter and std::ranges::to
    return {};
}

int main() {
    std::vector<int> numbers = {3, -2, 17, 0, -5, 8};
    std::println("{}", positive(numbers));
}
