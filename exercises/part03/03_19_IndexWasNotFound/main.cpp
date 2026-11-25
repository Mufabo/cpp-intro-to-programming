// Exercise 3.19: Index Was Not Found
// See chapter 3 of the book for the assignment.

#include <array>
#include <iostream>
#include <print>
#include <string>
#include <vector>

int main() {
    std::array<int, 10> array = {6, 2, 8, 1, 3, 0, 9, 7, 4, 5};

    std::println("Search for?");
    std::string line;
    std::getline(std::cin, line);
    int searched = std::stoi(line);

    // Write your code here
}
