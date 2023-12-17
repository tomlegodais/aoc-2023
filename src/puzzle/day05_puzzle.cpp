#include "puzzle/day_puzzle.hpp"
#include "util/utils.hpp"
#include <iostream>
#include <map>
#include <sstream>
#include <unordered_map>

using SectionMap = std::map<std::pair<long, long>, std::pair<long long, long long>>;
using SectionsMapping = std::unordered_map<std::string, SectionMap>;

SectionsMapping parseAllSections(const std::vector<std::string> &input) {
    SectionsMapping sections_mapping;
    std::string current_section;
    const SectionMap *current_map = nullptr;

    for (const auto &line: input) {
        if (line.empty()) {
            current_section.clear();
            current_map = nullptr;
            continue;
        }

        if (line.back() == ':') {
            current_section = line;
            current_map = &sections_mapping[current_section];
            continue;
        }

        if (current_map) {
            std::istringstream iss(line);
            int destination_start, source_start;
            if (int length; iss >> destination_start >> source_start >> length) {
                // TODO: Finish implementation
            }
        }
    }

    return sections_mapping;
}

template<>
int DayPuzzle<5>::solvePartOne(PuzzleService &, const std::vector<std::string> &puzzle_input) {
    std::vector<std::string> lines = {
            "seeds: 79 14 55 13",
            "",
            "seed-to-soil map:",
            "50 98 2",
            "52 50 48",
            "",
            "soil-to-fertilizer map:",
            "0 15 37",
            "37 52 2",
            "39 0 15",
            "",
            "fertilizer-to-water map:",
            "49 53 8",
            "0 11 42",
            "42 0 7",
            "57 7 4",
            "",
            "water-to-light map:",
            "88 18 7",
            "18 25 70",
            "",
            "light-to-temperature map:",
            "45 77 23",
            "81 45 19",
            "68 64 13",
            "",
            "temperature-to-humidity map:",
            "0 69 1",
            "1 0 69",
            "",
            "humidity-to-location map:",
            "60 56 37",
            "56 93 4"};

    std::vector<int> seeds_vector;
    for (auto &line: puzzle_input) {
        if (line.find("seeds: ") != std::string::npos) {
            std::string seeds = line.substr(line.find("seeds: ") + 7);
            std::stringstream ss(seeds);
            int seed;
            while (ss >> seed) {
                seeds_vector.push_back(seed);
            }
        }
    }

    const auto sections_mapping = parseAllSections(puzzle_input);

    return 0;
}

template<>
int DayPuzzle<5>::solvePartTwo(PuzzleService &, const std::vector<std::string> &puzzle_input) {
    return 0;
}

template<>
const char *DayPuzzle<5>::getTitle() {
    return "If You Give A Seed A Fertilizer";
}