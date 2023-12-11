#include <sstream>
#include "puzzle/day02_puzzle.hpp"
#include <algorithm>
#include <iostream>
#include "util/string_utils.hpp"
#include <map>
#include <numeric>
#include <ranges>

const std::map<std::string, int> COLOR_MAPPING = {
    {"red", 12},
    {"green", 13},
    {"blue", 14}
};

std::vector<std::string> Day02Puzzle::parseGroups(const std::string& line)
{
    std::istringstream iss(line.substr(line.find(':') + 1));
    std::vector<std::string> groups;
    std::string group;

    while (std::getline(iss, group, ';'))
    {
        groups.push_back(group);
    }

    return groups;
}

std::map<std::string, int> Day02Puzzle::countColors(const std::string& group)
{
    std::map<std::string, int> colorCounts;
    std::istringstream groupStream(group);
    std::string pair;

    while (std::getline(groupStream, pair, ','))
    {
        std::istringstream pairStream(pair);
        int count;
        std::string color;

        pairStream >> count >> color;
        colorCounts[color] += count;
    }

    return colorCounts;
}

bool Day02Puzzle::isGroupValid(const std::string& group)
{
    const auto& colorCounts = countColors(group);
    return std::ranges::all_of(COLOR_MAPPING.begin(), COLOR_MAPPING.end(), [&colorCounts](const auto& pair)
    {
        const auto& [color, max] = pair;
        auto it = colorCounts.find(color);
        return it == colorCounts.end() || it->second <= max;
    });
}


int Day02Puzzle::solvePartOne(std::string& puzzleInput)
{
    const auto& lines = StringUtils::splitOnNewline(puzzleInput);
    int sum = 0;

    for (const auto& line: lines)
    {
        auto groups = parseGroups(line);
        bool possible = true;

        for (const auto& group: groups)
        {
            if (isGroupValid(group)) continue;

            possible = false;
            break;
        }

        const int id = static_cast<int>(&line - &lines[0] + 1);
        if (possible) sum += id;
    }

    return sum;
}

std::vector<int> Day02Puzzle::getHighestValues(const std::map<std::string, std::vector<int>>& totalCounts)
{
    std::vector<int> highestValues;

    for (const auto& counts: totalCounts | std::views::values)
    {
        if (!counts.empty())
        {
            highestValues.push_back(*std::ranges::max_element(counts));
        }
    }

    return highestValues;
}

int Day02Puzzle::solvePartTwo(std::string& puzzleInput)
{
    const auto& lines = StringUtils::splitOnNewline(puzzleInput);
    int sum = 0;

    for (const auto& line: lines)
    {
        auto groups = parseGroups(line);
        std::map<std::string, std::vector<int>> totalCounts;

        for (const auto& group: groups)
        {
            for (const auto& [color, count]: countColors(group))
            {
                totalCounts[color].push_back(count);
            }
        }

        const auto& highestValues = getHighestValues(totalCounts);
        const int power = std::accumulate(highestValues.begin(), highestValues.end(), 1, std::multiplies());

        sum += power;
    }
    return sum;
}

[[maybe_unused]] PuzzleRegistrar<2, Day02Puzzle> Day02Puzzle::registrar("Cube Conundrum");
