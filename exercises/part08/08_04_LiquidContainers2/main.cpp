// Exercise 8.4: Liquid Containers 2.0
// See chapter 7 (recap in chapter 8) of the book for the assignment.

#include <iostream>
#include <print>
#include <string>

// Create the file Container.h and then uncomment the include below.
// #include "Container.h"

int main() {
    // Container first;
    // Container second;

    std::string line;
    while (true) {
        // print the containers here

        std::getline(std::cin, line);
        if (line == "quit") {
            break;
        }

        std::size_t space = line.find(' ');
        if (space == std::string::npos) {
            continue;
        }
        std::string command = line.substr(0, space);
        int amount = std::stoi(line.substr(space + 1));

        // Write your code here
    }
}
