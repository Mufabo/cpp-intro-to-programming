#pragma once

#include <format>
#include <string>

class Book {
public:
    Book(int id, const std::string& name) : id(id), name(name) {
    }

    int getId() const { return id; }
    std::string getName() const { return name; }

    std::string toString() const {
        return std::format("({}, {})", id, name);
    }

private:
    int id;
    std::string name;
};
