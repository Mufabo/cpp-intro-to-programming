#pragma once

#include <format>
#include <string>

// An immutable amount of money: no member function changes an existing object.
class Money {
public:
    Money(int euros, int cents) {
        if (cents > 99) {
            euros = euros + cents / 100;
            cents = cents % 100;
        }
        euros_ = euros;
        cents_ = cents;
    }

    int euros() const { return euros_; }
    int cents() const { return cents_; }

    // Part 1: Money plus(const Money& addition) const
    // Part 2: bool lessThan(const Money& compared) const
    // Part 3: Money minus(const Money& decreaser) const

    std::string toString() const {
        return std::format("{}.{:02}e", euros_, cents_);
    }

private:
    int euros_;
    int cents_;
};
