#pragma once

#include <optional>
#include <print>
#include <string>
#include <vector>
#include "Item.h"

// Rewrite the loops of this class with range algorithms and views.
class Suitcase {
public:
    Suitcase(int maxWeight) : maxWeight(maxWeight) {
    }

    void addItem(const Item& item) {
        if (totalWeight() + item.getWeight() > maxWeight) {
            return;
        }
        items.push_back(item);
    }

    int totalWeight() const {
        int sum = 0;
        for (const Item& item : items) {
            sum += item.getWeight();
        }
        return sum;
    }

    void printItems() const {
        for (const Item& item : items) {
            std::println("{}", item.toString());
        }
    }

    std::optional<Item> heaviestItem() const {
        if (items.empty()) {
            return std::nullopt;
        }
        Item heaviest = items[0];
        for (const Item& item : items) {
            if (item.getWeight() > heaviest.getWeight()) {
                heaviest = item;
            }
        }
        return heaviest;
    }

    std::string toString() const {
        if (items.empty()) {
            return "no items (0 kg)";
        }
        if (items.size() == 1) {
            return std::format("1 item ({} kg)", totalWeight());
        }
        return std::format("{} items ({} kg)", items.size(), totalWeight());
    }

private:
    int maxWeight;
    std::vector<Item> items;
};
