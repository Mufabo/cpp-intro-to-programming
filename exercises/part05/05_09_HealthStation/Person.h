#pragma once

#include <string>

class Person {
public:
    Person(const std::string& name, int age, int height, int weight)
        : name(name), age(age), height(height), weight(weight) {
    }

    std::string getName() const { return name; }
    int getAge() const { return age; }
    int getHeight() const { return height; }
    int getWeight() const { return weight; }

    void setWeight(int newWeight) { weight = newWeight; }

private:
    std::string name;
    int age;
    int height;
    int weight;
};
