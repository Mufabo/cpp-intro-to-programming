// Exercise 8.9: Print Me Another Hash Map
// See chapter 8 of the book for the assignment.

#include <iostream>
#include <map>
#include <print>
#include <string>
#include "Book.h"

void printValues(const std::map<std::string, Book>& map) {
}

void printValueIfNameContains(const std::map<std::string, Book>& map, const std::string& text) {
}

int main() {
    std::map<std::string, Book> map;
    map.emplace("sense", Book("Sense and Sensibility", 1811, "..."));
    map.emplace("prejudice", Book("Pride and prejudice", 1813, "...."));

    printValues(map);
    std::println("---");
    printValueIfNameContains(map, "prejud");
}
