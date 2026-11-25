#pragma once

#include <vector>
#include "Item.h"

class Box {
public:
    virtual ~Box() = default;

    virtual void add(const Item& item) = 0;

    void add(const std::vector<Item>& items) {
        for (const Item& item : items) {
            add(item);
        }
    }

    virtual bool isInBox(const Item& item) const = 0;
};
