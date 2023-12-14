#include "puzzle/day03_puzzle.hpp"
#include "util/string_utils.hpp"
#include <iostream>
#include <set>

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

int findPartNumber(const std::vector<std::string> &schematic, int x, int y) {
    if (x >= 0 && x < schematic.size() && y >= 0 && y < schematic[0].size() && isdigit(schematic[x][y])) {
        while (y > 0 && isdigit(schematic[x][y - 1])) {
            y--;
        }

        std::string numberStr;
        while (y < schematic[x].size() && isdigit(schematic[x][y])) {
            numberStr += schematic[x][y];
            y++;
        }

        return std::stoi(numberStr);
    }

    return -1;
}

int Day03Puzzle::solvePartTwo(std::string &puzzle_input) {
    const std::vector<std::string> schematic = StringUtils::splitOnNewline(puzzle_input);
    int totalSum = 0;

    for (int i = 0; i < schematic.size(); i++) {
        for (int j = 0; j < schematic[i].size(); j++) {
            if (schematic[i][j] == '*') {
                std::set<int> adjacentNumbers;

                for (int dx = -1; dx <= 1; dx++) {
                    for (int dy = -1; dy <= 1; dy++) {
                        if (dx == 0 && dy == 0) continue;

                        if (int partNumber = findPartNumber(schematic, i + dx, j + dy); partNumber != -1)
                            adjacentNumbers.insert(partNumber);
                    }
                }

                if (adjacentNumbers.size() == 2) {
                    auto it = adjacentNumbers.begin();
                    totalSum += *it * *++it;
                }
            }
        }
    }

    return totalSum;
}

[[maybe_unused]] PuzzleRegistrar<3, Day03Puzzle> Day03Puzzle::registrar_("Gear Ratios");
