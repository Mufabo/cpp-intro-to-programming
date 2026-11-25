// Exercise 3.4: List Size
// See chapter 3 of the book for the assignment.

#include <iostream>
#include <print>
#include <string>
#include <vector>

int main() {
    std::vector<std::string> list;
    std::string line;
    while (true) {
        std::getline(std::cin, line);
        if (line.empty()) {
            break;
        }
        list.push_back(line);
    }

    // Print the number of values here
}
