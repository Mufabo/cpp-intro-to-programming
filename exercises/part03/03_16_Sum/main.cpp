// Exercise 3.16: Sum
// See chapter 3 of the book for the assignment.

#include <iostream>
#include <print>
#include <string>
#include <vector>

int sum(const std::vector<int>& numbers) {
    // Write your code here
    return 0;
}

int main() {
    std::vector<int> numbers = {3, 2, 6, -1};
    std::println("{}", sum(numbers));

    numbers.push_back(5);
    numbers.push_back(1);
    std::println("{}", sum(numbers));
}
