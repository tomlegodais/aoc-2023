#include "puzzle/day03_puzzle.hpp"
#include "util/string_utils.hpp"
#include <iostream>
#include <set>

bool Day03Puzzle::isSymbol(const char c) {
    return !isdigit(c) && c != '.';
}

bool Day03Puzzle::isAdjacent(const std::vector<std::string> &schematic, const int x, const int y) {
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            const int new_x = x + dx;
            if (const int new_y = y + dy; new_x >= 0 && new_x < schematic.size() && new_y >= 0 && new_y < schematic[0].size() && isSymbol(schematic[new_x][new_y])) {
                return true;
            }
        }
    }
    return false;
}

int Day03Puzzle::solvePartOne(std::string &puzzle_input) {
    const std::vector<std::string> schematic = StringUtils::splitOnNewline(puzzle_input);
    int total_sum = 0;

    for (int i = 0; i < schematic.size(); i++) {
        for (int j = 0; j < schematic[i].size(); j++) {
            if ((j == 0 || !isdigit(schematic[i][j - 1])) && isdigit(schematic[i][j])) {
                std::string numberStr;
                int k = j;
                bool adjacent_to_symbol = false;
                while (k < schematic[i].size() && isdigit(schematic[i][k])) {
                    numberStr += schematic[i][k];
                    if (isAdjacent(schematic, i, k)) adjacent_to_symbol = true;
                    k++;
                }
                if (adjacent_to_symbol) {
                    total_sum += std::stoi(numberStr);
                }
                j = k - 1;
            }
        }
    }

    return total_sum;
}

int Day03Puzzle::findPartNumber(const std::vector<std::string> &schematic, const int x, int y) {
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
    int total_sum = 0;

    for (int i = 0; i < schematic.size(); i++) {
        for (int j = 0; j < schematic[i].size(); j++) {
            if (schematic[i][j] == '*') {
                std::set<int> adjacent_numbers;

                for (int dx = -1; dx <= 1; dx++) {
                    for (int dy = -1; dy <= 1; dy++) {
                        if (dx == 0 && dy == 0) continue;

                        if (int part_number = findPartNumber(schematic, i + dx, j + dy); part_number != -1)
                            adjacent_numbers.insert(part_number);
                    }
                }

                if (adjacent_numbers.size() == 2) {
                    auto it = adjacent_numbers.begin();
                    total_sum += *it * *++it;
                }
            }
        }
    }

    return total_sum;
}

[[maybe_unused]] PuzzleRegistrar<3, Day03Puzzle> Day03Puzzle::registrar_("Gear Ratios");
