#pragma once

#include <print>

class DecreasingCounter {
public:
    DecreasingCounter(int initialValue) : value(initialValue) {
    }

    void printValue() const {
        std::println("value: {}", value);
    }

    void decrement() {
        // write the implementation here
        // the aim is to decrement the value of the counter by one
    }

    // and the other member functions go here

private:
    int value;   // the counter's value
};
