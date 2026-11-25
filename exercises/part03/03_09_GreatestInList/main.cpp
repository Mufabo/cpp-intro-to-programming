// Exercise 3.9: Greatest in List
// See chapter 3 of the book for the assignment.

#include <iostream>
#include <print>
#include <string>
#include <vector>

int main() {
    std::vector<int> list;
    std::string line;
    while (true) {
        std::getline(std::cin, line);
        int number = std::stoi(line);
        if (number == -1) {
            break;
        }
        list.push_back(number);
    }

    // Find and print the greatest number here
}
