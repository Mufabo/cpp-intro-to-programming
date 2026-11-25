// Exercise 6.11: Averages
// See chapter 6 of the book for the assignment.

#include <iostream>
#include <print>
#include <string>
#include "GradeRegister.h"
#include "UserInterface.h"

int main() {
    GradeRegister reg;
    UserInterface ui(reg, std::cin);
    ui.start();
}
