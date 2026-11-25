#pragma once

#include <iostream>
#include <print>
#include <string>
#include "TodoDao.h"

class UserInterface {
public:
    UserInterface(std::istream& input, TodoDao& dao) : input(input), dao(dao) {
    }

    void start() {
        std::string command;
        while (true) {
            std::println("");
            std::println("Enter command:");
            std::getline(input, command);

            if (command == "x") {
                break;
            } else if (command == "add") {
                std::println("Name:");
                std::string name;
                std::getline(input, name);
                std::println("Description:");
                std::string description;
                std::getline(input, description);
                dao.add(Todo(name, description, false));
            } else if (command == "list") {
                std::println("Listing the database contents");
                for (const Todo& todo : dao.list()) {
                    std::println("{}", todo.toString());
                }
            } else if (command == "mark as done") {
                std::println("Which todo should be marked as done (give the id)?");
                dao.markAsDone(readId());
            } else if (command == "remove") {
                std::println("Which todo should be removed (give the id)?");
                dao.remove(readId());
            }
        }
        std::println("Thank you!");
    }

private:
    int readId() {
        std::string line;
        std::getline(input, line);
        try {
            return std::stoi(line);
        } catch (const std::exception&) {
            return -1;
        }
    }

    std::istream& input;
    TodoDao& dao;
};
