// Exercise 8.8: Print Me My Hash Map
// See chapter 8 of the book for the assignment.

#include <iostream>
#include <map>
#include <print>
#include <string>

void printKeys(const std::map<std::string, std::string>& map) {
}

void printKeysWhere(const std::map<std::string, std::string>& map, const std::string& text) {
}

void printValuesOfKeysWhere(const std::map<std::string, std::string>& map, const std::string& text) {
}

int main() {
    std::map<std::string, std::string> map;
    map["f.e"] = "for example";
    map["etc."] = "and so on";
    map["i.e"] = "more precisely";

    printKeys(map);
    std::println("---");
    printKeysWhere(map, "i");
    std::println("---");
    printValuesOfKeysWhere(map, ".e");
}
