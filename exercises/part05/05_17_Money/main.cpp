// Exercise 5.17: Money
// See chapter 5 of the book for the assignment.

#include <iostream>
#include <print>
#include <string>
#include "Money.h"

int main() {
    Money a(10, 0);
    Money b(5, 0);
    std::println("{}", a.toString());
    std::println("{}", b.toString());
}
