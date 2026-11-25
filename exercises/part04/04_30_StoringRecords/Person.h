#pragma once

#include <format>
#include <string>

class Person {
public:
    Person(const std::string& name, int age) : name(name), age(age) {
    }

    std::string getName() const { return name; }
    int getAge() const { return age; }

    std::string toString() const {
        return std::format("{}, age {}", name, age);
    }

private:
    std::string name;
    int age;
};
