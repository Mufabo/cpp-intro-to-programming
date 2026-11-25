// Exercise 9.3: Warehousing
// See chapter 9 of the book for the assignment.

#include <iostream>
#include <print>
#include <string>
#include "Warehouse.h"

int main() {
    // You can test your classes here
    Warehouse warehouse(100);
    warehouse.addToWarehouse(64.5);
    std::println("{}", warehouse.toString());
}
