#include "puzzle/day_puzzle.hpp"
#include <set>

bool is_symbol(const char c) {
    return !isdigit(c) && c != '.';
}

bool is_adjacent(const std::vector<std::string> &schematic, const int x, const int y) {
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            const int new_x = x + dx;
            if (const int new_y = y + dy; new_x >= 0 && new_x < schematic.size() && new_y >= 0 && new_y < schematic[0].size() && is_symbol(schematic[new_x][new_y])) {
                return true;
            }
        }
    }
    return false;
}

int find_part_number(const std::vector<std::string> &schematic, const int x, int y) {
    if (x >= 0 && x < schematic.size() && y >= 0 && y < schematic[0].size() && isdigit(schematic[x][y])) {
        while (y > 0 && isdigit(schematic[x][y - 1])) {
            y--;
        }

        std::string number_str;
        while (y < schematic[x].size() && isdigit(schematic[x][y])) {
            number_str += schematic[x][y];
            y++;
        }

        return std::stoi(number_str);
    }

    return -1;
}

template<>
int DayPuzzle<3>::solve_part_one(PuzzleService &, const std::vector<std::string> &puzzle_input) {
    int total_sum = 0;

    for (int i = 0; i < puzzle_input.size(); i++) {
        for (int j = 0; j < puzzle_input[i].size(); j++) {
            if ((j == 0 || !isdigit(puzzle_input[i][j - 1])) && isdigit(puzzle_input[i][j])) {
                std::string number_str;
                int k = j;
                bool adjacent_to_symbol = false;
                while (k < puzzle_input[i].size() && isdigit(puzzle_input[i][k])) {
                    number_str += puzzle_input[i][k];
                    if (is_adjacent(puzzle_input, i, k)) adjacent_to_symbol = true;
                    k++;
                }
                if (adjacent_to_symbol) {
                    total_sum += std::stoi(number_str);
                }
                j = k - 1;
            }
        }
    }

    return total_sum;
}

template<>
int DayPuzzle<3>::solve_part_two(PuzzleService &, const std::vector<std::string> &puzzle_input) {
    int total_sum = 0;

    for (int i = 0; i < puzzle_input.size(); i++) {
        for (int j = 0; j < puzzle_input[i].size(); j++) {
            if (puzzle_input[i][j] == '*') {
                std::set<int> adjacent_numbers;

                for (int dx = -1; dx <= 1; dx++) {
                    for (int dy = -1; dy <= 1; dy++) {
                        if (dx == 0 && dy == 0) continue;

                        if (int part_number = find_part_number(puzzle_input, i + dx, j + dy); part_number != -1)
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

template<>
const char *DayPuzzle<3>::get_title() {
    return "Gear Ratios";
}