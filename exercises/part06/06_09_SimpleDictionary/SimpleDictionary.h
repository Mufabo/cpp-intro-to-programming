#pragma once

#include <map>
#include <optional>
#include <string>

// Stores words and their translations. It uses std::map, which you will meet
// in chapter 8 -- you only need to use the public member functions.
class SimpleDictionary {
public:
    void add(const std::string& word, const std::string& translation) {
        translations[word] = translation;
    }

    std::optional<std::string> translate(const std::string& word) const {
        auto found = translations.find(word);
        if (found == translations.end()) {
            return std::nullopt;
        }
        return found->second;
    }

private:
    std::map<std::string, std::string> translations;
};
