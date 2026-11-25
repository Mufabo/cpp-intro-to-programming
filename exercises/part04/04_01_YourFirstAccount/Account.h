#pragma once

#include <format>
#include <string>

// A bank account with an owner description and a balance. Do not modify.
class Account {
public:
    Account(const std::string& owner, double balance)
        : owner_(owner), balance_(balance) {
    }

    void deposit(double amount) {
        balance_ = balance_ + amount;
    }

    void withdraw(double amount) {
        balance_ = balance_ - amount;
    }

    double balance() const {
        return balance_;
    }

    std::string toString() const {
        return std::format("{} {}", owner_, balance_);
    }

private:
    std::string owner_;
    double balance_;
};
