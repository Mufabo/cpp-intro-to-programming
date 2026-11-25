// Exercise 3.2: Second Plus Third
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
        if (number == 0) {
            break;
        }
        list.push_back(number);
    }

    // Change this to print the sum of the second and third values
    std::println("{}", list[0]);
}
