#pragma once

#include <format>
#include <string>

class Book {
public:
    Book(const std::string& name, int publicationYear, const std::string& contents)
        : name(name), publicationYear(publicationYear), contents(contents) {
    }

    std::string getName() const { return name; }
    int getPublicationYear() const { return publicationYear; }
    std::string getContents() const { return contents; }

    std::string toString() const {
        return std::format("Name: {} ({})\nContents: {}", name, publicationYear, contents);
    }

private:
    std::string name;
    int publicationYear;
    std::string contents;
};
