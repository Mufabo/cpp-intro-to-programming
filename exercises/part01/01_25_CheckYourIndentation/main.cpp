// Exercise 1.25: Check Your Indentation
// See chapter 1 of the book for the assignment.

#include <iostream>
#include <print>
#include <string>

// This program works, but its indentation is a mess.
// Fix the indentation so that the structure of the code is easy to see.
int main() {
std::string line;
        std::println("Give a number:");
  std::getline(std::cin, line);
            int number = std::stoi(line);
if (number > 0) {
std::println("The number is positive.");
      if (number > 100) {
std::println("It is also quite large.");
    }
        } else {
  std::println("The number is not positive.");
              }
     std::println("Bye!");
}
