#pragma once

#include <string>
#include <vector>
#include "Todo.h"

struct sqlite3;

// Data access object: stores Todo objects in an SQLite database.
class TodoDao {
public:
    explicit TodoDao(const std::string& databaseFile);
    ~TodoDao();

    TodoDao(const TodoDao&) = delete;              // owns a database connection:
    TodoDao& operator=(const TodoDao&) = delete;   // copying is not allowed

    std::vector<Todo> list() const;
    void add(const Todo& todo);
    void markAsDone(int id);
    void remove(int id);

private:
    sqlite3* db = nullptr;
};
