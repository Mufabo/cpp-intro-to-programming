// Exercise 7.1: Liquid Containers
// See chapter 7 of the book for the assignment.

#include <iostream>
#include <print>
#include <string>

int main() {
    int first = 0;
    int second = 0;

    std::string line;
    while (true) {
        std::println("First: {}/100", first);
        std::println("Second: {}/100", second);

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
