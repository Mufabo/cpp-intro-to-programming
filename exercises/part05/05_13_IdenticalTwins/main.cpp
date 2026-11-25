// Exercise 5.13: Identical Twins
// See chapter 5 of the book for the assignment.

#include <iostream>
#include <print>
#include <string>
#include "Person.h"
#include "SimpleDate.h"

int main() {
    SimpleDate date(24, 3, 2017);
    SimpleDate date2(23, 7, 2017);

    Person leo("Leo", date, 62, 9);
    Person lily("Lily", date2, 65, 8);

    // Uncomment when operator== exists:
    // if (leo == lily) {
    //     std::println("Is this quite correct?");
    // }
    // Person leoWithDifferentWeight("Leo", date, 62, 10);
    // if (leo == leoWithDifferentWeight) {
    //     std::println("Is this quite correct?");
    // }
}
