#include "puzzle/day04_puzzle.hpp"
#include "util/string_utils.hpp"
#include <algorithm>
#include <sstream>

std::pair<std::vector<int>, std::vector<int>> Day04Puzzle::extractNumbers(const std::string &str) {
    const auto start_of_numbers = str.find(':');
    if (start_of_numbers == std::string::npos) {
        return {};
    }

    auto number_str = str.substr(start_of_numbers + 1);
    const auto pipe_pos = number_str.find('|');
    if (pipe_pos == std::string::npos) {
        return {};
    }

    const auto left_part = number_str.substr(0, pipe_pos);
    const auto right_part = number_str.substr(pipe_pos + 1);
    const auto number_vector = [](const std::string &num_str) {
        std::istringstream iss(num_str);
        std::vector<int> numbers;

        int num;
        while (iss >> num) numbers.push_back(num);

        return numbers;
    };

    const auto left_numbers = number_vector(left_part);
    const auto right_numbers = number_vector(right_part);
    return {left_numbers, right_numbers};
}

int Day04Puzzle::solvePartOne(std::vector<std::string> &puzzle_input) {
    int total_sum = 0;

    for (const auto &line: puzzle_input) {
        auto [left_numbers, right_numbers] = extractNumbers(line);

        std::vector<int> left_sort = left_numbers,
                         right_sort = right_numbers;

        std::ranges::sort(left_sort);
        std::ranges::sort(right_sort);

        std::vector<int> intersection;
        std::ranges::set_intersection(left_sort, right_sort,
                                      std::back_inserter(intersection));

        auto const match_count = intersection.size();
        int points = 0;
        if (match_count != 0) {
            points = 1 << match_count - 1;
        }

        total_sum += points;
    }

    return total_sum;
}

int Day04Puzzle::solvePartTwo(std::vector<std::string> &puzzle_input) {
    return 0;
}

[[maybe_unused]] PuzzleRegistrar<4, Day04Puzzle> Day04Puzzle::registrar_("Scratchcards");
