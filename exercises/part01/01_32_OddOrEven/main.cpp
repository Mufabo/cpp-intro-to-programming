// Exercise 1.32: Odd or Even
// See chapter 1 of the book for the assignment.

#include <iostream>
#include <print>
#include <string>

int main() {
    std::string line;
    std::println("Give a number:");
    std::getline(std::cin, line);
    int number = std::stoi(line);

    // Write your program here.
    // Hint: the remainder of a division is computed with the % operator.
    // number % 2 is 0 when the number is even, and 1 (or -1) when it is odd.
}
