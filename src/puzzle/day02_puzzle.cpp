#include <sstream>
#include "puzzle/day02_puzzle.hpp"
#include "util/string_utils.hpp"

int Day02Puzzle::solvePartOne(std::string &puzzleInput) {
    auto lines = StringUtils::splitOnNewline("Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green");
    for (const auto &line: lines) {
        std::map<std::string, int> colorCounts;
        std::istringstream iss(line.substr(line.find(':') + 1));

        std::string group;
        while (std::getline(iss, group, ';')) {
            std::istringstream groupStream(group);
            std::string pair;

            while (std::getline(groupStream, pair, ',')) {
                std::istringstream pairStream(pair);
                int count;
                std::string color;

                pairStream >> count >> color;
                colorCounts[color] += count;
            }
        }

        // TODO: Finish this
    }

    return 0;
}

int Day02Puzzle::solvePartTwo(std::string &puzzleInput) {
    return 0;
}

[[maybe_unused]] PuzzleRegistrar<2, Day02Puzzle> Day02Puzzle::registrar("Cube Conundrum");