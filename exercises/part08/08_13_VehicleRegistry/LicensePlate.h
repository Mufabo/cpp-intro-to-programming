#pragma once

#include <functional>
#include <string>

class LicensePlate {
public:
    LicensePlate(const std::string& country, const std::string& liNumber)
        : liNumber(liNumber), country(country) {
    }

    std::string toString() const {
        return country + " " + liNumber;
    }

    // Part 1: add operator== here (and a hash function below the class)

private:
    std::string liNumber;
    std::string country;
};
