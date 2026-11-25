// Exercise 3.31: Name of the Oldest
// See chapter 3 of the book for the assignment.

#include <iostream>
#include <print>
#include <string>
#include <vector>

// Splits text into parts at every occurrence of the delimiter.
std::vector<std::string> split(const std::string& text, char delimiter) {
    std::vector<std::string> parts;
    std::size_t start = 0;
    while (true) {
        std::size_t end = text.find(delimiter, start);
        if (end == std::string::npos) {
            parts.push_back(text.substr(start));
            break;
        }
        parts.push_back(text.substr(start, end - start));
        start = end + 1;
    }
    return parts;
}

int main() {
    // Write your program here
}
