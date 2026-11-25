// Exercise 14.10: Database
// See chapter 14 of the book for the assignment.

#include <iostream>
#include "TodoDao.h"
#include "UserInterface.h"

int main() {
    TodoDao dao("todos.db");
    UserInterface ui(std::cin, dao);
    ui.start();
}
