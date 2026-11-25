// Exercise 4.8: Decreasing Counter
// See chapter 4 of the book for the assignment.

#include <iostream>
#include <print>
#include <string>
#include "DecreasingCounter.h"

int main() {
    DecreasingCounter counter(10);
    counter.printValue();
    counter.decrement();
    counter.printValue();
    counter.decrement();
    counter.printValue();
}
