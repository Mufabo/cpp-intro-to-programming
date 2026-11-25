// Exercise 5.14: Books
// See chapter 5 of the book for the assignment.

#include <algorithm>
#include <iostream>
#include <print>
#include <string>
#include <vector>
#include "Book.h"

int main() {
    std::vector<Book> books;
    std::string line;

    while (true) {
        std::println("Name (empty will stop):");
        std::string name;
        std::getline(std::cin, name);
        if (name.empty()) {
            break;
        }

        std::println("Publication year:");
        std::getline(std::cin, line);
        int publicationYear = std::stoi(line);
        Book book(name, publicationYear);

        books.push_back(book);
    }

    std::println("Thank you! Books added: {}", books.size());
}
