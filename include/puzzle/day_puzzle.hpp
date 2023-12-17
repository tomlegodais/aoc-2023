#pragma once

#include "service/puzzle_service.hpp"
#include <vector>

template<int Day>
class DayPuzzle {
public:
    static constexpr int day = Day;

    static int solvePartOne(PuzzleService &, const std::vector<std::string> &);

    static int solvePartTwo(PuzzleService &, const std::vector<std::string> &);

    static const char *getTitle();
};

template<>
int DayPuzzle<1>::solvePartOne(PuzzleService &, const std::vector<std::string> &);

template<>
int DayPuzzle<1>::solvePartTwo(PuzzleService &, const std::vector<std::string> &);

template<>
const char *DayPuzzle<1>::getTitle();