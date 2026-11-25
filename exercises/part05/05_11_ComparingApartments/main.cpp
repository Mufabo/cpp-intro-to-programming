// Exercise 5.11: Comparing Apartments
// See chapter 5 of the book for the assignment.

#include <iostream>
#include <print>
#include <string>
#include "Apartment.h"

int main() {
    Apartment manhattanStudioApt(1, 16, 5500);
    Apartment atlantaTwoBedroomApt(2, 38, 4200);
    Apartment bangorThreeBedroomApt(3, 78, 2500);

    // Uncomment when the member functions exist:
    // std::println("{}", manhattanStudioApt.largerThan(atlantaTwoBedroomApt));     // false
    // std::println("{}", bangorThreeBedroomApt.largerThan(atlantaTwoBedroomApt));  // true
}
