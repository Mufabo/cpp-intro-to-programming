#pragma once

#include <format>
#include <functional>
#include <string>

class SimpleDate {
public:
    SimpleDate(int day, int month, int year) : day(day), month(month), year(year) {
    }

    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }

    std::string toString() const {
        return std::format("{}.{}.{}", day, month, year);
    }

    bool earlier(const SimpleDate& other) const {
        if (year != other.year) {
            return year < other.year;
        }
        if (month != other.month) {
            return month < other.month;
        }
        return day < other.day;
    }

    int differenceInYears(const SimpleDate& other) const {
        if (earlier(other)) {
            return other.differenceInYears(*this);
        }
        int yearRemoved = 0;
        if (month < other.month || (month == other.month && day < other.day)) {
            yearRemoved = 1;
        }
        return year - other.year - yearRemoved;
    }

    bool operator==(const SimpleDate& other) const = default;

    std::size_t hashCode() const {
        // Calculate a good hash here
        return 0;
    }

private:
    int day;
    int month;
    int year;
};

// Lets SimpleDate be used as a key of std::unordered_map.
template <>
struct std::hash<SimpleDate> {
    std::size_t operator()(const SimpleDate& date) const {
        return date.hashCode();
    }
};
