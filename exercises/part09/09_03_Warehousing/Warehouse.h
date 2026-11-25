#pragma once

#include <format>
#include <string>

class Warehouse {
public:
    Warehouse(double capacity) {
        if (capacity > 0.0) {
            this->capacity = capacity;
        }
    }

    // Make toString, addToWarehouse and takeFromWarehouse virtual,
    // and add a virtual destructor.

    double getBalance() const { return balance; }
    double getCapacity() const { return capacity; }
    double howMuchSpaceLeft() const { return capacity - balance; }

    void addToWarehouse(double amount) {
        if (amount < 0) {
            return;
        }
        if (amount <= howMuchSpaceLeft()) {
            balance = balance + amount;
        } else {
            balance = capacity;
        }
    }

    double takeFromWarehouse(double amount) {
        if (amount < 0) {
            return 0.0;
        }
        if (amount > balance) {
            double allThatWeCan = balance;
            balance = 0.0;
            return allThatWeCan;
        }
        balance = balance - amount;
        return amount;
    }

    std::string toString() const {
        return std::format("balance = {:.1f}, space left {:.1f}", balance, howMuchSpaceLeft());
    }

private:
    double capacity = 0.0;
    double balance = 0.0;
};
