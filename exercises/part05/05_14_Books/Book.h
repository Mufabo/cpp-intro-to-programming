#pragma once

#include <string>

class Book {
public:
    Book(const std::string& name, int publicationYear)
        : name(name), publicationYear(publicationYear) {
    }

    std::string getName() const { return name; }
    int getPublicationYear() const { return publicationYear; }

private:
    std::string name;
    int publicationYear;
};
