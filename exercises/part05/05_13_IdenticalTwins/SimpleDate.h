#pragma once

#include <format>
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

    bool before(const SimpleDate& compared) const {
        if (year != compared.year) {
            return year < compared.year;
        }
        if (month != compared.month) {
            return month < compared.month;
        }
        return day < compared.day;
    }

private:
    int day;
    int month;
    int year;
};
