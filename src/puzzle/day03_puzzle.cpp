#include "puzzle/day03_puzzle.hpp"
#include "util/string_utils.hpp"
#include <iostream>

bool isSymbol(const char c) {
    return !isdigit(c) && c != '.';
}

bool isAdjacent(const std::vector<std::string> &schematic, const int x, const int y) {
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            const int newX = x + dx;
            if (const int newY = y + dy; newX >= 0 && newX < schematic.size() && newY >= 0 && newY < schematic[0].size() && isSymbol(schematic[newX][newY])) {
                return true;
            }
        }
    }
    return false;
}

int Day03Puzzle::solvePartOne(std::string &puzzle_input) {
    const std::vector<std::string> schematic = StringUtils::splitOnNewline(puzzle_input);
    int totalSum = 0;

    for (int i = 0; i < schematic.size(); i++) {
        for (int j = 0; j < schematic[i].size(); j++) {
            if ((j == 0 || !isdigit(schematic[i][j - 1])) && isdigit(schematic[i][j])) {
                std::string numberStr;
                int k = j;
                bool adjacentToSymbol = false;
                while (k < schematic[i].size() && isdigit(schematic[i][k])) {
                    numberStr += schematic[i][k];
                    if (isAdjacent(schematic, i, k)) adjacentToSymbol = true;
                    k++;
                }
                if (adjacentToSymbol) {
                    totalSum += std::stoi(numberStr);
                }
                j = k - 1;
            }
        }
    }

    return totalSum;
}

int Day03Puzzle::solvePartTwo(std::string &puzzle_input) {
    return 0;
}

[[maybe_unused]] PuzzleRegistrar<3, Day03Puzzle> Day03Puzzle::registrar_("Gear Ratios");
