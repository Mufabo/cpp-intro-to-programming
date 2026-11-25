#pragma once

#include <format>
#include <string>
#include <vector>
#include "Suitcase.h"

// Rewrite the loops of this class with range algorithms and views.
class Hold {
public:
    Hold(int maxWeight) : maxWeight(maxWeight) {
    }

    void addSuitcase(const Suitcase& suitcase) {
        if (totalWeight() + suitcase.totalWeight() > maxWeight) {
            return;
        }
        suitcases.push_back(suitcase);
    }

    int totalWeight() const {
        int sum = 0;
        for (const Suitcase& suitcase : suitcases) {
            sum += suitcase.totalWeight();
        }
        return sum;
    }

    void printItems() const {
        for (const Suitcase& suitcase : suitcases) {
            suitcase.printItems();
        }
    }

    std::string toString() const {
        return std::format("{} suitcases ({} kg)", suitcases.size(), totalWeight());
    }

private:
    int maxWeight;
    std::vector<Suitcase> suitcases;
};
