#include "puzzle/day_puzzle.hpp"
#include <iostream>
#include <map>
#include <numeric>
#include <ranges>
#include <sstream>
#include <unordered_map>

using Race = std::pair<int, int>;
using RaceMap = std::map<int, Race>;

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
        const auto &[time, distance] = race;

        for (int i = 0; i < time; ++i) {
            const int remaining_time = time - current_speed;
            if (const int distance_traveled = current_speed * remaining_time; distance_traveled > distance) {
                winning_counts[race_id]++;
            }

            current_speed++;
        }
    }

    return std::accumulate(winning_counts.begin(), winning_counts.end(), 1,
                           [](const int &acc, const auto &pair) { return acc * pair.second; });
}

template<typename T>
T merge_integers(const T merged, const T value) {
    static_assert(std::is_integral_v<T>, "T must be an integral type");
    if (value == 0) return merged * 10;

    const int digits = static_cast<T>(log10(value)) + 1;
    return merged * static_cast<T>(pow(10, digits)) + value;
}

template<>
int DayPuzzle<6>::solvePartTwo(PuzzleService &, const std::vector<std::string> &puzzle_input) {
    const auto race_mapping = parseRaces(puzzle_input);
    long long merged_time = 0, merged_distance = 0;
    for (const auto &[time, distance]: race_mapping | std::views::values) {
        merged_time = merge_integers(merged_time, static_cast<long long>(time));
        merged_distance = merge_integers(merged_distance, static_cast<long long>(distance));
    }

    long long current_speed = 0, winning_count = 0;
    for (int i = 0; i < merged_time; ++i) {
        const long long remaining_time = merged_time - current_speed;
        if (const long long distance_traveled = current_speed * remaining_time; distance_traveled > merged_distance) {
            winning_count++;
        }

        current_speed++;
    }

    return winning_count;
}

template<>
const char *DayPuzzle<6>::getTitle() {
    return "Wait For It";
}