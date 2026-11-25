// Exercise 3.3: Out of Range
// See chapter 3 of the book for the assignment.

#include <iostream>
#include <print>
#include <string>
#include <vector>

int main() {
    // Modify this program so that it always ends in an std::out_of_range error.

    std::vector<std::string> lines;
    lines.push_back("Few physicists shaped the twentieth century like Niels Bohr.");
    lines.push_back("In the early 1900s almost nothing was known about the structure of atoms,");
    lines.push_back("and Bohr spent decades building and testing models of them.");
    lines.push_back("His model of the atom became a stepping stone to quantum mechanics.");

    for (std::size_t i = 0; i < lines.size(); i++) {
        std::println("{}", lines.at(i));
    }
}
