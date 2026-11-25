#include "TodoDao.h"

#include <stdexcept>
#include "sqlite3.h"

TodoDao::TodoDao(const std::string& databaseFile) {
    if (sqlite3_open(databaseFile.c_str(), &db) != SQLITE_OK) {
        throw std::runtime_error("Cannot open database " + databaseFile);
    }
    const char* createTable =
        "CREATE TABLE IF NOT EXISTS Todo ("
        " id INTEGER PRIMARY KEY AUTOINCREMENT,"
        " name TEXT, description TEXT, done INTEGER)";
    sqlite3_exec(db, createTable, nullptr, nullptr, nullptr);
}

TodoDao::~TodoDao() {
    sqlite3_close(db);
}

std::vector<Todo> TodoDao::list() const {
    std::vector<Todo> todos;
    sqlite3_stmt* statement = nullptr;
    sqlite3_prepare_v2(db, "SELECT id, name, description, done FROM Todo", -1, &statement, nullptr);
    while (sqlite3_step(statement) == SQLITE_ROW) {
        int id = sqlite3_column_int(statement, 0);
        std::string name = reinterpret_cast<const char*>(sqlite3_column_text(statement, 1));
        std::string description = reinterpret_cast<const char*>(sqlite3_column_text(statement, 2));
        bool done = sqlite3_column_int(statement, 3) != 0;
        todos.emplace_back(id, name, description, done);
    }
    sqlite3_finalize(statement);
    return todos;
}

void TodoDao::add(const Todo& todo) {
    sqlite3_stmt* statement = nullptr;
    sqlite3_prepare_v2(db, "INSERT INTO Todo (name, description, done) VALUES (?, ?, ?)",
                       -1, &statement, nullptr);
    sqlite3_bind_text(statement, 1, todo.getName().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(statement, 2, todo.getDescription().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(statement, 3, todo.isDone() ? 1 : 0);
    sqlite3_step(statement);
    sqlite3_finalize(statement);
}

void TodoDao::markAsDone(int id) {
    // Implement: UPDATE Todo SET done = 1 WHERE id = ?
}

void TodoDao::remove(int id) {
    // Implement: DELETE FROM Todo WHERE id = ?
}
