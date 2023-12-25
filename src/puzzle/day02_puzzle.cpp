#include "puzzle/day_puzzle.hpp"
#include <algorithm>
#include <map>
#include <numeric>
#include <ranges>
#include <sstream>

const std::map<std::string, int> color_mapping = {
        {"red", 12},
        {"green", 13},
        {"blue", 14}};

std::vector<std::string> parse_groups(const std::string &line) {
    std::istringstream iss(line.substr(line.find(':') + 1));
    std::vector<std::string> groups;
    std::string group;

    while (std::getline(iss, group, ';')) {
        groups.push_back(group);
    }

    return groups;
}

std::map<std::string, int> count_colors(const std::string &group) {
    std::map<std::string, int> color_counts;
    std::istringstream group_stream(group);
    std::string pair;

    while (std::getline(group_stream, pair, ',')) {
        std::istringstream pair_stream(pair);
        int count;
        std::string color;

        pair_stream >> count >> color;
        color_counts[color] += count;
    }

    return color_counts;
}

bool is_group_valid(const std::string &group) {
    const auto &color_counts = count_colors(group);
    return std::ranges::all_of(color_mapping.begin(), color_mapping.end(), [&color_counts](const auto &pair) {
        const auto &[color, max] = pair;
        auto it = color_counts.find(color);
        return it == color_counts.end() || it->second <= max;
    });
}

std::vector<int> get_highest_values(const std::map<std::string, std::vector<int>> &total_counts) {
    std::vector<int> highest_values;

    for (const auto &counts: total_counts | std::views::values) {
        if (!counts.empty()) {
            highest_values.push_back(*std::ranges::max_element(counts));
        }
    }

    return highest_values;
}

template<>
PuzzleResult DayPuzzle<2>::solve_part_one(PuzzleService &, const std::vector<std::string> &puzzle_input) {
    int sum = 0;

    for (const auto &line: puzzle_input) {
        auto groups = parse_groups(line);
        bool possible = true;

        for (const auto &group: groups) {
            if (is_group_valid(group)) continue;

            possible = false;
            break;
        }

        const int id = static_cast<int>(&line - &puzzle_input[0] + 1);
        if (possible) sum += id;
    }

    return sum;
}

template<>
PuzzleResult DayPuzzle<2>::solve_part_two(PuzzleService &, const std::vector<std::string> &puzzle_input) {
    int sum = 0;

    for (const auto &line: puzzle_input) {
        auto groups = parse_groups(line);
        std::map<std::string, std::vector<int>> total_counts;

        for (const auto &group: groups) {
            for (const auto &[color, count]: count_colors(group)) {
                total_counts[color].push_back(count);
            }
        }

        const auto &highest_values = get_highest_values(total_counts);
        const int power = std::accumulate(highest_values.begin(), highest_values.end(), 1, std::multiplies());

        sum += power;
    }
    return sum;
}

template<>
const char *DayPuzzle<2>::get_title() {
    return "Cube Conundrum";
}