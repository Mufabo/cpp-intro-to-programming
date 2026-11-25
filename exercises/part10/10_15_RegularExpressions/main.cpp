// Exercise 10.15: Regular Expressions
// See chapter 10 of the book for the assignment.

#include <iostream>
#include <print>
#include <regex>
#include <string>

bool isDayOfWeek(const std::string& text) {
    return false;
}

bool allVowels(const std::string& text) {
    return false;
}

bool timeOfDay(const std::string& text) {
    return false;
}

int main() {
    std::println("Enter a string:");
    std::string text;
    std::getline(std::cin, text);

    // Change the function called here to test each part
    if (isDayOfWeek(text)) {
        std::println("The form is correct.");
    } else {
        std::println("The form is incorrect.");
    }
}
