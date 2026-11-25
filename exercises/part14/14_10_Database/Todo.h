#pragma once

#include <format>
#include <string>

class Todo {
public:
    Todo(int id, const std::string& name, const std::string& description, bool done)
        : id(id), name(name), description(description), done(done) {
    }

    Todo(const std::string& name, const std::string& description, bool done)
        : Todo(-1, name, description, done) {
    }

    int getId() const { return id; }
    std::string getName() const { return name; }
    std::string getDescription() const { return description; }
    bool isDone() const { return done; }

    std::string toString() const {
        return std::format("{}, {}, {}, {}", id, name, description, done);
    }

private:
    int id;
    std::string name;
    std::string description;
    bool done;
};
