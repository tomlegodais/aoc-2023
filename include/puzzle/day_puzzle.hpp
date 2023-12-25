#pragma once

#include "service/puzzle_service.hpp"
#include <variant>
#include <vector>

using PuzzleResult = std::variant<int, long long>;

template<int Day>
class DayPuzzle {
public:
    static constexpr int day = Day;

    PuzzleResult solve_part_one(PuzzleService &, const std::vector<std::string> &);

    PuzzleResult solve_part_two(PuzzleService &, const std::vector<std::string> &);

    static const char *get_title();
};