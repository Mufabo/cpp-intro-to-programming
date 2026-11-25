#pragma once

#include <string>

// Do not modify this class.
class PersonalInformation {
public:
    PersonalInformation(const std::string& firstName, const std::string& lastName,
                        const std::string& identificationNumber)
        : firstName(firstName), lastName(lastName), identificationNumber(identificationNumber) {
    }

    std::string getFirstName() const { return firstName; }
    std::string getLastName() const { return lastName; }
    std::string getIdentificationNumber() const { return identificationNumber; }

    std::string toString() const {
        return lastName + ", " + firstName + " (" + identificationNumber + ")";
    }

private:
    std::string firstName;
    std::string lastName;
    std::string identificationNumber;
};
