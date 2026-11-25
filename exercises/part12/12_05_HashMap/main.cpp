// Exercise 12.5: Hash Map
// See chapter 12 of the book for the assignment.

#include <iostream>
#include <print>
#include <string>
#include "HashMap.h"

int main() {
    HashMap<std::string, int> ages;
    ages.add("ada", 36);
    ages.add("grace", 85);
    std::println("{}", ages.get("ada").value_or(-1));
    std::println("{}", ages.get("alan").value_or(-1));
}
