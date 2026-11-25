// Exercise 4.30: Storing Records
// See chapter 4 of the book for the assignment.

#include <fstream>
#include <iostream>
#include <print>
#include <string>
#include <vector>
#include "Person.h"
#include "split.h"

std::vector<Person> readRecordsFromFile(const std::string& fileName) {
    std::vector<Person> persons;
    // Write here the code for reading from the file
    // and for adding the persons to the vector
    return persons;
}

int main() {
    std::println("Name of the file:");
    std::string fileName;
    std::getline(std::cin, fileName);

    std::vector<Person> records = readRecordsFromFile(fileName);
    std::println("Persons: {}", records.size());
    std::println("Persons:");
    for (const Person& person : records) {
        std::println("{}", person.toString());
    }
}
