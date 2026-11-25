// Exercise 3.10: Index Of
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

    // Ask for a number and print its indices here
}
