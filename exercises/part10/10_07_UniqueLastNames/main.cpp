// Exercise 10.7: Unique Last Names
// See chapter 10 of the book for the assignment.

#include <algorithm>
#include <functional>
#include <iostream>
#include <print>
#include <ranges>
#include <set>
#include <string>
#include <vector>
#include "Person.h"

int main() {
    std::vector<Person> persons;
    std::string line;

    // reading person information
    while (true) {
        std::println("Continue personal information input? \"quit\" ends:");
        std::getline(std::cin, line);
        if (line == "quit") {
            break;
        }

        std::println("Input first name:");
        std::string firstName;
        std::getline(std::cin, firstName);
        std::println("Input last name:");
        std::string lastName;
        std::getline(std::cin, lastName);
        std::println("Input the year of birth:");
        std::getline(std::cin, line);
        int birthYear = std::stoi(line);
        persons.emplace_back(firstName, lastName, birthYear);
        std::println("");
    }

    // implement printing the unique last names in alphabetical order here
}
