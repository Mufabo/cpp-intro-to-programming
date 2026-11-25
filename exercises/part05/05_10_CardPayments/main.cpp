// Exercise 5.10: Card Payments
// See chapter 5 of the book for the assignment.

#include <iostream>
#include <print>
#include <string>
#include "PaymentCard.h"
#include "PaymentTerminal.h"

int main() {
    PaymentCard petesCard(10);
    std::println("money {}", petesCard.balance());
    bool wasSuccessful = petesCard.takeMoney(8);
    std::println("successfully took: {}", wasSuccessful);
    std::println("money {}", petesCard.balance());
    wasSuccessful = petesCard.takeMoney(4);
    std::println("successfully took: {}", wasSuccessful);
    std::println("money {}", petesCard.balance());
}
