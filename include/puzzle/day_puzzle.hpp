#pragma once

#include "service/puzzle_service.hpp"

class DayPuzzle {
protected:
    PuzzleService puzzle_service_;

public:
    explicit DayPuzzle(const PuzzleService &puzzle_service) : puzzle_service_(puzzle_service) {}

    virtual ~DayPuzzle() = default;

    virtual int solvePartOne(std::vector<std::string> &puzzle_input) = 0;

    virtual int solvePartTwo(std::vector<std::string> &puzzle_input) = 0;
};
