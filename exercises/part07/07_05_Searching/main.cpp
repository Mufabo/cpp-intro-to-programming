// Exercise 7.5: Searching
// See chapter 7 of the book for the assignment.

#include <chrono>
#include <iostream>
#include <print>
#include <string>
#include <vector>
#include "Book.h"

int linearSearch(const std::vector<Book>& books, int searchedId) {
    // implement linear search here
    return -1;
}

int binarySearch(const std::vector<Book>& books, int searchedId) {
    // implement binary search here
    return -1;
}

int main() {
    std::println("How many books to create?");
    std::string line;
    std::getline(std::cin, line);
    int numberOfBooks = std::stoi(line);

    std::vector<Book> books;
    for (int i = 0; i < numberOfBooks; i++) {
        books.emplace_back(i, "name for the book");
    }

    std::println("Id of the book to search for?");
    std::getline(std::cin, line);
    int idToSearchFor = std::stoi(line);

    std::println("");
    std::println("Searching with linear search:");
    auto start = std::chrono::steady_clock::now();
    int linearSearchIndex = linearSearch(books, idToSearchFor);
    auto elapsed = std::chrono::steady_clock::now() - start;
    std::println("The search took {} microseconds.",
                 std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count());
    if (linearSearchIndex < 0) {
        std::println("The book was not found.");
    } else {
        std::println("Found it! {}", books[linearSearchIndex].toString());
    }

    std::println("");
    std::println("Searching with binary search:");
    start = std::chrono::steady_clock::now();
    int binarySearchIndex = binarySearch(books, idToSearchFor);
    elapsed = std::chrono::steady_clock::now() - start;
    std::println("The search took {} microseconds.",
                 std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count());
    if (binarySearchIndex < 0) {
        std::println("The book was not found.");
    } else {
        std::println("Found it! {}", books[binarySearchIndex].toString());
    }
}
