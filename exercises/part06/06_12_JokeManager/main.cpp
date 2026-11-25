// Exercise 6.12: Joke Manager
// See chapter 6 of the book for the assignment.

#include <iostream>
#include <print>
#include <random>
#include <string>
#include <vector>

// This program works, but everything is in main. Split it into the classes
// JokeManager and UserInterface as described in the book.
int main() {
    std::vector<std::string> jokes;
    std::mt19937 engine{std::random_device{}()};
    std::string command;

    while (true) {
        std::println("Commands:");
        std::println(" 1 - add a joke");
        std::println(" 2 - draw a joke");
        std::println(" 3 - list jokes");
        std::println(" X - stop");

        std::getline(std::cin, command);
        if (command == "X") {
            break;
        }

        if (command == "1") {
            std::println("Write the joke to be added:");
            std::string joke;
            std::getline(std::cin, joke);
            jokes.push_back(joke);
        } else if (command == "2") {
            std::println("Drawing a joke.");
            if (jokes.empty()) {
                std::println("Jokes are in short supply.");
            } else {
                std::uniform_int_distribution<std::size_t> pick(0, jokes.size() - 1);
                std::println("{}", jokes[pick(engine)]);
            }
        } else if (command == "3") {
            std::println("Printing the jokes.");
            for (const std::string& joke : jokes) {
                std::println("{}", joke);
            }
        }
    }
}
