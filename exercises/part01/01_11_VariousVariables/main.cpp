// Exercise 1.11: Various Variables
// See chapter 1 of the book for the assignment.

#include <iostream>
#include <print>
#include <string>

int main() {
    // MODIFY THESE:
    int numberOfChicken = 3;
    double baconWeight = 5.5;
    std::string tractor = "None!";

    // DON'T MODIFY THESE:
    std::println("Chicken:");
    std::println("{}", numberOfChicken);
    std::println("Bacon (kg):");
    std::println("{}", baconWeight);
    std::println("Tractor:");
    std::println("{}", tractor);
    std::println("");
    std::println("And finally, a summary:");
    std::println("{}", numberOfChicken);
    std::println("{}", baconWeight);
    std::println("{}", tractor);
}
