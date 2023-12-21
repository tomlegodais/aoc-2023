#include "puzzle/day_puzzle.hpp"

#include <iostream>
#include <numeric>
#include <ranges>
#include <sstream>
#include <unordered_map>

using Race = std::pair<int, int>;
using RaceMap = std::unordered_map<int, Race>;

RaceMap parseRaces(const std::vector<std::string> &input) {
    RaceMap race_mapping;
    int line_id = 0;

    for (const auto &line: input) {
        std::istringstream iss(line.substr(line.find(':') + 1));
        int race_id = 0, value;

        while (iss >> value) {
            if (line_id == 0) race_mapping.emplace(race_id++, std::make_pair(value, -1));
            else
                race_mapping[race_id++].second = value;
        }

        ++line_id;
    }

    return race_mapping;
}

template<>
int DayPuzzle<6>::solvePartOne(PuzzleService &, const std::vector<std::string> &puzzle_input) {
    const auto race_mapping = parseRaces(puzzle_input);
    std::unordered_map<int, int> winning_counts;

    for (const auto &[race_id, race]: race_mapping) {
        int current_speed = 0;
        const auto &[distance, time] = race;

        for (int i = 0; i < distance; ++i) {
            const int remaining_time = distance - current_speed;
            if (const int distance_traveled = current_speed * remaining_time; distance_traveled > time) {
                winning_counts[race_id]++;
            }

            current_speed++;
        }
    }

    return std::accumulate(winning_counts.begin(), winning_counts.end(), 1,
                           [](const int &acc, const auto &pair) { return acc * pair.second; });
}

template<>
int DayPuzzle<6>::solvePartTwo(PuzzleService &, const std::vector<std::string> &puzzle_input) {
    return 0;
}

template<>
const char *DayPuzzle<6>::getTitle() {
    return "Wait For It";
}