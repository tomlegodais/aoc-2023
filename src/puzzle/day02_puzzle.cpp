#include <sstream>
#include "puzzle/day02_puzzle.hpp"
#include "util/string_utils.hpp"
#include <map>

const std::map<std::string, int> COLOR_MAPPING = {
        {"red",   12},
        {"green", 13},
        {"blue",  14}
};

int Day02Puzzle::solvePartOne(std::string &puzzleInput) {
    auto lines = StringUtils::splitOnNewline(puzzleInput);
    int sum = 0;

    for (auto i = 0; i < lines.size(); i++) {
        const auto &line = lines[i];
        std::istringstream iss(line.substr(line.find(':') + 1));

        std::string group;
        bool possible = true;

        while (std::getline(iss, group, ';')) {
            std::map<std::string, int> colorCounts;
            std::istringstream groupStream(group);
            std::string pair;

            while (std::getline(groupStream, pair, ',')) {
                std::istringstream pairStream(pair);
                int count;
                std::string color;

                pairStream >> count >> color;
                colorCounts[color] += count;
            }

            for (const auto & [fst, snd]: COLOR_MAPPING) {
                const auto &color = fst;

                if (const auto &max = snd; colorCounts[color] > max) {
                    possible = false;
                    break;
                }
            }
        }

        if (possible) sum += i + 1;
    }

    return sum;
}

int Day02Puzzle::solvePartTwo(std::string &puzzleInput) {
    return 0;
}

[[maybe_unused]] PuzzleRegistrar<2, Day02Puzzle> Day02Puzzle::registrar("Cube Conundrum");