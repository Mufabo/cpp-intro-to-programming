// Exercise 8.13: Vehicle Registry
// See chapter 8 of the book for the assignment.

#include <algorithm>
#include <iostream>
#include <print>
#include <string>
#include <unordered_map>
#include <vector>
#include "LicensePlate.h"

int main() {
    LicensePlate li1("FI", "ABC-123");
    LicensePlate li2("FI", "UXE-465");
    LicensePlate li3("D", "B WQ-431");

    // Uncomment when operator== and std::hash<LicensePlate> exist:
    // std::vector<LicensePlate> finnishPlates = {li1, li2};
    // LicensePlate newLi("FI", "ABC-123");
    // if (!std::ranges::contains(finnishPlates, newLi)) {
    //     finnishPlates.push_back(newLi);
    // }
    // std::println("finnish: {}", finnishPlates.size());
    //
    // std::unordered_map<LicensePlate, std::string> owners;
    // owners[li1] = "Arto";
    // owners[li3] = "Jürgen";
    // owners[LicensePlate("FI", "ABC-123")] = "Arto";
    // std::println("owners: {}", owners.size());
}
