// Exercise 5.16: Dating App
// See chapter 5 of the book for the assignment.

#include <iostream>
#include <print>
#include <string>
#include "SimpleDate.h"

int main() {
    SimpleDate date(13, 2, 2015);
    std::println("Friday of the examined week is {}", date.toString());

    // Uncomment when afterNumberOfDays exists:
    // SimpleDate newDate = date.afterNumberOfDays(7);
    // int week = 1;
    // while (week <= 7) {
    //     std::println("Friday after {} weeks is {}", week, newDate.toString());
    //     newDate = newDate.afterNumberOfDays(7);
    //     week = week + 1;
    // }
}
