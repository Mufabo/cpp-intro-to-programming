#pragma once

class PaymentCard {
public:
    PaymentCard(double balance) : balance_(balance) {
    }

    double balance() const {
        return balance_;
    }

    void addMoney(double increase) {
        balance_ = balance_ + increase;
    }

    bool takeMoney(double amount) {
        // implement the function so that it only takes money from the card if
        // the balance is at least the amount parameter.
        // returns true if successful and false otherwise
        return false;
    }

private:
    double balance_;
};
