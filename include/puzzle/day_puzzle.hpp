#pragma once

#include "service/puzzle_service.hpp"
#include <vector>

template<int Day>
class DayPuzzle {
public:
    static constexpr int day = Day;

    static int solve_part_one(PuzzleService &, const std::vector<std::string> &);

    static int solve_part_two(PuzzleService &, const std::vector<std::string> &);

    static const char *get_title();
};