#include "puzzle/day01_puzzle.hpp"
#include "util/string_utils.hpp"
#include <algorithm>

int Day01Puzzle::solvePartOne(std::string &puzzle_input) {
    const auto lines = StringUtils::splitOnNewline(puzzle_input);
    int sum = 0;

    for (const auto &line: lines) {
        int first_digit = 0, last_digit = 0;
        for (const auto &c: line) {
            if (std::isdigit(c)) {
                if (first_digit == 0) first_digit = c - '0';
                last_digit = c - '0';
            }
        }

        sum += first_digit * 10 + last_digit;
    }

    return sum;
}

int Day01Puzzle::solvePartTwo(std::string &puzzle_input) {
    const auto lines = StringUtils::splitOnNewline(puzzle_input);
    const std::map<std::string, char> number_mapping = {
            {"one", 1},
            {"two", 2},
            {"three", 3},
            {"four", 4},
            {"five", 5},
            {"six", 6},
            {"seven", 7},
            {"eight", 8},
            {"nine", 9},
    };

    int sum = 0;
    for (const auto &line: lines) {
        std::vector<std::pair<int, int>> indices;
        for (auto i = 0; i < line.length(); i++) {
            if (std::isalpha(line[i])) {
                for (const auto &[fst, snd]: number_mapping) {
                    if (const std::string &word = fst; line.substr(i, word.length()) == word) {
                        indices.emplace_back(i, snd);
                        break;
                    }
                }
            } else if (std::isdigit(line[i])) {
                indices.emplace_back(i, line[i] - '0');
            }
        }

        std::ranges::sort(indices, [](const auto &lhs, const auto &rhs) {
            return lhs.first < rhs.first;
        });

        const int first_digit = indices[0].second;
        const int last_digit = indices[indices.size() - 1].second;

        sum += first_digit * 10 + last_digit;
    }

    return sum;
}

[[maybe_unused]] PuzzleRegistrar<1, Day01Puzzle> Day01Puzzle::registrar_("Trebuchet?!");
