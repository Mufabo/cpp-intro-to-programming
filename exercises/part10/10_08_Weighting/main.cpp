// Exercise 10.8: Weighting
// See chapter 10 of the book for the assignment.

#include <algorithm>
#include <iostream>
#include <print>
#include <ranges>
#include <string>
#include "Hold.h"
#include "Item.h"
#include "Suitcase.h"

int main() {
    Item book("Lord of the rings", 2);
    Item phone("Nokia 3210", 1);
    Item brick("Brick", 4);

    Suitcase adasCase(10);
    adasCase.addItem(book);
    adasCase.addItem(phone);

    Suitcase pekkasCase(10);
    pekkasCase.addItem(brick);

    Hold hold(1000);
    hold.addSuitcase(adasCase);
    hold.addSuitcase(pekkasCase);

    std::println("The suitcases in the hold contain the following items:");
    hold.printItems();
    std::println("{}", hold.toString());
}
