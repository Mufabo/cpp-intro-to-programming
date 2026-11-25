// Exercise 10.10: Books from File
// See chapter 10 of the book for the assignment.

#include <fstream>
#include <iostream>
#include <print>
#include <ranges>
#include <string>
#include <vector>
#include "Book.h"
#include "split.h"

std::vector<Book> readBooks(const std::string& fileName) {
    return {};
}

int main() {
    for (const Book& book : readBooks("books.txt")) {
        std::println("{}", book.toString());
    }
}
