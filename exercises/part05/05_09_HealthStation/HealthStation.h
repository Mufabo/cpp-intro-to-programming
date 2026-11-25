#pragma once

#include "Person.h"

class HealthStation {
public:
    int weigh(const Person& person) {
        // return the weight of the person passed as the parameter
        return -1;
    }

    void feed(Person& person) {
        // increase the person's weight by one
    }

    int weighings() const {
        // return how many weighings have been done
        return 0;
    }
};
