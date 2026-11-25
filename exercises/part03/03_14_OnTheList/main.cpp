// Exercise 3.14: On the List?
// See chapter 3 of the book for the assignment.

#include <algorithm>
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

    // Ask for a name and tell whether it is on the list
}
