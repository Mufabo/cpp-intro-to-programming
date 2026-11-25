// Exercise 12.7: Die
// See chapter 12 of the book for the assignment.

#include <iostream>
#include <print>
#include <string>
#include "Die.h"

int main() {
    Die die(6);
    for (int i = 0; i < 10; i++) {
        std::println("{}", die.throwDie());
    }
}
