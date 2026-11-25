#pragma once

#include <cstddef>
#include <functional>
#include <optional>
#include <utility>
#include <vector>

template <typename K, typename V>
class HashMap {
public:
    HashMap() : buckets(32) {
    }

    std::optional<V> get(const K& key) const {
        // Part 1
        return std::nullopt;
    }

    void add(const K& key, const V& value) {
        // Part 1 (and call grow() when the table gets too full in part 2)
    }

    // Part 3: std::optional<V> remove(const K& key)

private:
    std::size_t indexOf(const K& key) const {
        return std::hash<K>{}(key) % buckets.size();
    }

    void grow() {
        // Part 2
    }

    std::vector<std::vector<std::pair<K, V>>> buckets;
    std::size_t count = 0;
};
