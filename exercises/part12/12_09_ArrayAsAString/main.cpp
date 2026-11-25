// Exercise 12.9: Array as a String
// See chapter 12 of the book for the assignment.

#include <iostream>
#include <print>
#include <string>
#include <vector>

std::string arrayAsString(const std::vector<std::vector<int>>& array) {
    return "";
}

int main() {
    std::vector<std::vector<int>> matrix(2, std::vector<int>(3, 0));
    matrix[0][1] = 5;
    matrix[1][0] = 3;
    matrix[1][2] = 7;
    std::println("{}", arrayAsString(matrix));
}
