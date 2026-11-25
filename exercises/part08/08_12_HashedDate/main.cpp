// Exercise 8.12: Hash for Date
// See chapter 8 of the book for the assignment.

#include <iostream>
#include <print>
#include <string>
#include <unordered_set>
#include "SimpleDate.h"

int main() {
    // Count the distinct hash values of (simplified, 30-day-month) dates
    // between the years 1900 and 2100. The closer to the number of dates, the better.
    std::unordered_set<std::size_t> hashes;
    int dates = 0;
    for (int year = 1900; year <= 2100; year++) {
        for (int month = 1; month <= 12; month++) {
            for (int day = 1; day <= 30; day++) {
                hashes.insert(SimpleDate(day, month, year).hashCode());
                dates++;
            }
        }
    }
    std::println("{} dates, {} different hash values", dates, hashes.size());
}
