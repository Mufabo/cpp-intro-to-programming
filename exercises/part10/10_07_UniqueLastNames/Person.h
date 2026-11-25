#pragma once

#include <format>
#include <string>

class Person {
public:
    Person(const std::string& firstName, const std::string& lastName, int birthYear)
        : firstName(firstName), lastName(lastName), birthYear(birthYear) {
    }

    std::string getFirstName() const { return firstName; }
    std::string getLastName() const { return lastName; }
    int getBirthYear() const { return birthYear; }

    std::string toString() const {
        return std::format("{} {}", firstName, lastName);
    }

private:
    std::string firstName;
    std::string lastName;
    int birthYear;
};
