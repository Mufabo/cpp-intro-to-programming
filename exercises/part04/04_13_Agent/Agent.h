#pragma once

#include <print>
#include <string>

class Agent {
public:
    Agent(const std::string& firstName, const std::string& lastName)
        : firstName(firstName), lastName(lastName) {
    }

    void print() const {
        std::println("My name is {}, {} {}", lastName, firstName, lastName);
    }

private:
    std::string firstName;
    std::string lastName;
};
