#pragma once

#include <chrono>
#include <format>
#include <string>

// An item that remembers its name and the moment it was created. Do not modify.
class Item {
public:
    Item(const std::string& name)
        : name(name),
          createdAt(std::chrono::floor<std::chrono::seconds>(std::chrono::system_clock::now())) {
    }

    std::string toString() const {
        return std::format("{} (created at: {:%d.%m.%Y %H:%M:%S})", name, createdAt);
    }

private:
    std::string name;
    std::chrono::sys_seconds createdAt;
};
