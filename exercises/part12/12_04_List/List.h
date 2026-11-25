#pragma once

#include <cstddef>
#include <memory>
#include <stdexcept>
#include <utility>

template <typename T>
class List {
public:
    List() : values(std::make_unique<T[]>(10)), capacity(10) {
    }

    // Part 1: add, value, size and grow
    // Part 2: contains, indexOfValue and remove

private:
    std::unique_ptr<T[]> values;
    std::size_t capacity;
    std::size_t count = 0;
};
