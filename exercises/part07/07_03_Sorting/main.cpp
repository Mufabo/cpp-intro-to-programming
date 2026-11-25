// Exercise 7.3: Sorting
// See chapter 7 of the book for the assignment.

#include <iostream>
#include <print>
#include <span>
#include <string>
#include <vector>

int smallest(std::span<const int> numbers) {
    // write your code here
    return 0;
}

std::size_t indexOfSmallest(std::span<const int> numbers) {
    // write your code here
    return 0;
}

std::size_t indexOfSmallestFrom(std::span<const int> numbers, std::size_t startIndex) {
    // write your code here
    return 0;
}

void swap(std::span<int> numbers, std::size_t index1, std::size_t index2) {
    // write your code here
}

void sort(std::span<int> numbers) {
    // write your code here
}

int main() {
    std::vector<int> numbers = {8, 3, 7, 9, 1, 2, 4};
    sort(numbers);
    std::println("{}", numbers);
}
