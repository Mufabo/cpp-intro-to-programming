#pragma once

#include <iostream>
#include <print>
#include <string>
#include "GradeRegister.h"

class UserInterface {
public:
    UserInterface(GradeRegister& reg, std::istream& input) : reg(reg), input(input) {
    }

    void start() {
        readPoints();
        std::println("");
        printGradeDistribution();
    }

private:
    void readPoints() {
        std::string line;
        while (true) {
            std::print("Points: ");
            std::getline(input, line);
            if (line.empty()) {
                break;
            }
            int points = std::stoi(line);
            if (points < 0 || points > 100) {
                std::println("Impossible number.");
                continue;
            }
            reg.addGradeBasedOnPoints(points);
        }
    }

    void printGradeDistribution() {
        for (int grade = 5; grade >= 0; grade--) {
            std::println("{}: {}", grade, std::string(reg.numberOfGrades(grade), '*'));
        }
    }

    GradeRegister& reg;
    std::istream& input;
};
