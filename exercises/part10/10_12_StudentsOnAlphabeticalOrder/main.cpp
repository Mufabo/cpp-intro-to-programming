// Exercise 10.12: Students in Alphabetical Order
// See chapter 10 of the book for the assignment.

#include <algorithm>
#include <iostream>
#include <print>
#include <string>
#include <vector>
#include "Student.h"

int main() {
    std::vector<Student> students = {Student("Petra"), Student("Ada"), Student("Grace"), Student("Esko")};
    // Uncomment when the ordering exists:
    // std::ranges::sort(students);
    for (const Student& student : students) {
        std::println("{}", student.toString());
    }
}
