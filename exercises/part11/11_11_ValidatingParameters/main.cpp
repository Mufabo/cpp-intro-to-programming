// Exercise 11.11: Validating Parameters
// See chapter 11 of the book for the assignment.

#include <iostream>
#include <print>
#include <stdexcept>
#include <string>
#include "Calculator.h"
#include "Person.h"

int main() {
    try {
        Person person("", 30);
        std::println("Created {}", person.getName());
    } catch (const std::invalid_argument& error) {
        std::println("Invalid person: {}", error.what());
    }

    Calculator calculator;
    std::println("{}", calculator.binomialCoefficient(5, 2));
}
