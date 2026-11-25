#pragma once

#include <random>
#include <vector>

class LotteryRow {
public:
    LotteryRow() : engine(std::random_device{}()) {
        randomizeNumbers();
    }

    const std::vector<int>& numbers() const {
        return numbers_;
    }

    bool containsNumber(int number) const {
        // Test whether the number is already among the drawn numbers
        return false;
    }

    void randomizeNumbers() {
        numbers_.clear();
        // Draw seven different numbers from 1 to 40 here, using containsNumber
    }

private:
    std::mt19937 engine;
    std::vector<int> numbers_;
};
