// Exercise 4.15: Statistics
// See chapter 4 of the book for the assignment.

#include <iostream>
#include <print>
#include <string>
#include "Statistics.h"

int main() {
    Statistics statistics;
    statistics.addNumber(3);
    statistics.addNumber(5);
    statistics.addNumber(1);
    statistics.addNumber(2);
    std::println("Count: {}", statistics.getCount());
}
