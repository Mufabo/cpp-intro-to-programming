#pragma once

#include <format>
#include <string>
#include "PaymentCard.h"

class PaymentTerminal {
public:
    PaymentTerminal() {
        // the register initially has 1000 euros of money
    }

    double eatAffordably(double payment) {
        // an affordable meal costs 2.50 euros
        // increase the amount of cash by the price of an affordable meal and return the change
        // if the payment is not large enough, no meal is sold and the whole payment is returned
        return payment;
    }

    double eatHeartily(double payment) {
        // a hearty meal costs 4.30 euros
        // increase the amount of cash by the price of a hearty meal and return the change
        // if the payment is not large enough, no meal is sold and the whole payment is returned
        return payment;
    }

    std::string toString() const {
        return std::format("money: {}, number of sold affordable meals: {}, number of sold hearty meals: {}",
                           money, affordableMeals, heartyMeals);
    }

private:
    double money = 0;         // amount of cash
    int affordableMeals = 0;  // number of sold affordable meals
    int heartyMeals = 0;      // number of sold hearty meals
};
