#pragma once

#include <format>
#include <string>

class Song {
public:
    Song(const std::string& artist, const std::string& name, int durationInSeconds)
        : artist(artist), name(name), durationInSeconds(durationInSeconds) {
    }

    // Add operator== here

    std::string toString() const {
        return std::format("{}: {} ({} s)", artist, name, durationInSeconds);
    }

private:
    std::string artist;
    std::string name;
    int durationInSeconds;
};
