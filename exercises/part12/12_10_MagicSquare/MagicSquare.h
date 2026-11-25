#pragma once

#include <algorithm>
#include <set>
#include <string>
#include <vector>

class MagicSquare {
public:
    MagicSquare(int size) {
        if (size < 2) {
            size = 2;
        }
        square = std::vector<std::vector<int>>(size, std::vector<int>(size, 0));
    }

    // Part 1
    std::vector<int> sumsOfRows() const {
        return {};
    }

    // Part 2
    std::vector<int> sumsOfColumns() const {
        return {};
    }

    // Part 3
    std::vector<int> sumsOfDiagonals() const {
        return {};
    }

    // ready-made helpers -- no need to touch them

    bool isMagicSquare() const {
        return sumsAreSame() && allNumbersDifferent();
    }

    bool allNumbersDifferent() const {
        std::set<int> numbers;
        for (const auto& row : square) {
            numbers.insert(row.begin(), row.end());
        }
        return numbers.size() == static_cast<std::size_t>(getWidth() * getHeight());
    }

    bool sumsAreSame() const {
        std::vector<int> sums = sumsOfRows();
        std::vector<int> columns = sumsOfColumns();
        std::vector<int> diagonals = sumsOfDiagonals();
        sums.insert(sums.end(), columns.begin(), columns.end());
        sums.insert(sums.end(), diagonals.begin(), diagonals.end());
        if (sums.size() < 3) {
            return false;
        }
        return std::ranges::all_of(sums, [&](int sum) { return sum == sums[0]; });
    }

    int readValue(int x, int y) const {
        if (x < 0 || y < 0 || x >= getWidth() || y >= getHeight()) {
            return -1;
        }
        return square[y][x];
    }

    void placeValue(int x, int y, int value) {
        if (x < 0 || y < 0 || x >= getWidth() || y >= getHeight()) {
            return;
        }
        square[y][x] = value;
    }

    int getWidth() const { return static_cast<int>(square.size()); }
    int getHeight() const { return static_cast<int>(square.size()); }

    std::string toString() const {
        std::string result;
        for (const auto& row : square) {
            for (std::size_t i = 0; i < row.size(); i++) {
                result += std::to_string(row[i]);
                if (i + 1 < row.size()) {
                    result += " ";
                }
            }
            result += "\n";
        }
        return result;
    }

private:
    std::vector<std::vector<int>> square;
};
