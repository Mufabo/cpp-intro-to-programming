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

    std::string toString() const {
        std::string result = "The collection " + name;
        if (elements.empty()) {
            return result + " is empty.";
        }
        result += " has " + std::to_string(elements.size())
                  + (elements.size() == 1 ? " element:" : " elements:");
        for (const std::string& element : elements) {
            result += "\n" + element;
        }
        return result;
    }

    // Implement std::optional<std::string> longest() const here

private:
    std::string name;
    std::vector<std::string> elements;
};
