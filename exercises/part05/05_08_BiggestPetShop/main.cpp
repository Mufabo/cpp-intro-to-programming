// Exercise 5.8: Biggest Pet Shop
// See chapter 5 of the book for the assignment.

#include <iostream>
#include <print>
#include <string>
#include "Person.h"
#include "Pet.h"

int main() {
    Pet lucy("Lucy", "golden retriever");
    Person leo("Leo", lucy);
    std::println("{}", leo.toString());
}
