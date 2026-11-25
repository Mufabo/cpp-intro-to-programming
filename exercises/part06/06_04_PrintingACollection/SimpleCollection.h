#pragma once

#include <optional>
#include <string>
#include <vector>

class SimpleCollection {
public:
    SimpleCollection(const std::string& name) : name(name) {
    }

    void add(const std::string& element) {
        elements.push_back(element);
    }

    const std::vector<std::string>& getElements() const {
        return elements;
    }

    // Implement std::string toString() const here

private:
    std::string name;
    std::vector<std::string> elements;
};
