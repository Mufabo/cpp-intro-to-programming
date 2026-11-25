#pragma once

class Calculator {
public:
    int factorial(int num) const {
        // Part 2: validate the parameter here
        int answer = 1;
        for (int i = 1; i <= num; i++) {
            answer *= i;
        }
        return answer;
    }

    int binomialCoefficient(int setSize, int subsetSize) const {
        // Part 2: validate the parameters here
        int numerator = factorial(setSize);
        int denominator = factorial(subsetSize) * factorial(setSize - subsetSize);
        return numerator / denominator;
    }
};
