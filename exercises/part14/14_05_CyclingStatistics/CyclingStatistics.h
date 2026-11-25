#pragma once

#include <fstream>
#include <map>
#include <string>
#include <vector>

// Reads cycling-monthly.csv (station;year/month;cyclists).
class CyclingStatistics {
public:
    explicit CyclingStatistics(const std::string& fileName) {
        std::ifstream file(fileName);
        std::string line;
        std::getline(file, line);   // header
        while (std::getline(file, line)) {
            std::size_t first = line.find(';');
            std::size_t second = line.find(';', first + 1);
            if (first == std::string::npos || second == std::string::npos) {
                continue;
            }
            std::string station = line.substr(0, first);
            std::string month = line.substr(first + 1, second - first - 1);
            int count = std::stoi(line.substr(second + 1));
            data[station][month] = count;
        }
    }

    std::vector<std::string> stations() const {
        std::vector<std::string> names;
        for (const auto& [station, months] : data) {
            names.push_back(station);
        }
        return names;
    }

    // month ("2014/05") -> number of cyclists, in chronological order
    std::map<std::string, int> monthlyCyclists(const std::string& station) const {
        auto found = data.find(station);
        return found == data.end() ? std::map<std::string, int>{} : found->second;
    }

private:
    std::map<std::string, std::map<std::string, int>> data;
};
