#include "puzzle/day02_puzzle.hpp"
#include <algorithm>
#include <map>
#include <numeric>
#include <ranges>
#include <sstream>

const std::map<std::string, int> color_mapping = {
        {"red", 12},
        {"green", 13},
        {"blue", 14}};

std::vector<std::string> Day02Puzzle::parseGroups(const std::string &line) {
    std::istringstream iss(line.substr(line.find(':') + 1));
    std::vector<std::string> groups;
    std::string group;

    while (std::getline(iss, group, ';')) {
        groups.push_back(group);
    }

    return groups;
}

std::map<std::string, int> Day02Puzzle::countColors(const std::string &group) {
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

bool Day02Puzzle::isGroupValid(const std::string &group) {
    const auto &color_counts = countColors(group);
    return std::ranges::all_of(color_mapping.begin(), color_mapping.end(), [&color_counts](const auto &pair) {
        const auto &[color, max] = pair;
        auto it = color_counts.find(color);
        return it == color_counts.end() || it->second <= max;
    });
}

std::vector<int> Day02Puzzle::getHighestValues(const std::map<std::string, std::vector<int>> &total_counts) {
    std::vector<int> highest_values;

    for (const auto &counts: total_counts | std::views::values) {
        if (!counts.empty()) {
            highest_values.push_back(*std::ranges::max_element(counts));
        }
    }

    return highest_values;
}

int Day02Puzzle::solvePartOne(std::vector<std::string> &puzzle_input) {
    int sum = 0;

    for (const auto &line: puzzle_input) {
        auto groups = parseGroups(line);
        bool possible = true;

        for (const auto &group: groups) {
            if (isGroupValid(group)) continue;

            possible = false;
            break;
        }

        const int id = static_cast<int>(&line - &puzzle_input[0] + 1);
        if (possible) sum += id;
    }

    return sum;
}

int Day02Puzzle::solvePartTwo(std::vector<std::string> &puzzle_input) {
    int sum = 0;

    for (const auto &line: puzzle_input) {
        auto groups = parseGroups(line);
        std::map<std::string, std::vector<int>> total_counts;

        for (const auto &group: groups) {
            for (const auto &[color, count]: countColors(group)) {
                total_counts[color].push_back(count);
            }
        }

        const auto &highest_values = getHighestValues(total_counts);
        const int power = std::accumulate(highest_values.begin(), highest_values.end(), 1, std::multiplies());

        sum += power;
    }
    return sum;
}

[[maybe_unused]] PuzzleRegistrar<2, Day02Puzzle> Day02Puzzle::registrar_("Cube Conundrum");
