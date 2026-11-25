#pragma once

#include <string>

class Person {
public:
    Person(const std::string& name, int age) : name(name), age(age) {
        // Part 1: validate the parameters here
    }

    std::string getName() const { return name; }
    int getAge() const { return age; }

private:
    std::string name;
    int age;
};
