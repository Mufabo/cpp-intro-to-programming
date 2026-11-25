// Exercise 5.9: Health Station
// See chapter 5 of the book for the assignment.

#include <iostream>
#include <print>
#include <string>
#include "HealthStation.h"
#include "Person.h"

int main() {
    HealthStation childrensHospital;
    Person ethan("Ethan", 1, 110, 7);
    Person peter("Peter", 33, 176, 85);

    std::println("{}'s weight: {} kilos", ethan.getName(), childrensHospital.weigh(ethan));
    std::println("{}'s weight: {} kilos", peter.getName(), childrensHospital.weigh(peter));
}
