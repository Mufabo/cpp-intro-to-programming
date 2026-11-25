// Exercise 4.26: Guest List from a File
// See chapter 4 of the book for the assignment.

#include <algorithm>
#include <fstream>
#include <iostream>
#include <print>
#include <string>
#include <vector>

int main() {
    std::println("Name of the file:");
    std::string fileName;
    std::getline(std::cin, fileName);

    std::vector<std::string> list;
    // implement reading the file here.

    std::println("");
    std::println("Enter names, an empty line quits.");
    std::string name;
    while (true) {
        std::getline(std::cin, name);
        if (name.empty()) {
            break;
        }

        if (std::ranges::contains(list, name)) {
            std::println("The name is on the list.");
        } else {
            std::println("The name is not on the list.");
        }
    }

    std::println("Thank you!");
}
