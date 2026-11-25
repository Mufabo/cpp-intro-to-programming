#pragma once

#include <vector>

class GradeRegister {
public:
    void addGradeBasedOnPoints(int points) {
        grades.push_back(pointsToGrade(points));
    }

    int numberOfGrades(int grade) const {
        int count = 0;
        for (int received : grades) {
            if (received == grade) {
                count++;
            }
        }
        return count;
    }

    static int pointsToGrade(int points) {
        if (points < 50) return 0;
        if (points < 60) return 1;
        if (points < 70) return 2;
        if (points < 80) return 3;
        if (points < 90) return 4;
        return 5;
    }

private:
    std::vector<int> grades;
};
