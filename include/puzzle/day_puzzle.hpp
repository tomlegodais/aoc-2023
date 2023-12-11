#pragma once

#include "service/puzzle_service.hpp"

class DayPuzzle
{
protected:
    PuzzleService puzzleService_;

public:
    explicit DayPuzzle(const PuzzleService& puzzleService) : puzzleService_(puzzleService)
    {
        /* no-op */
    }

    virtual ~DayPuzzle() = default;

    virtual int solvePartOne(std::string& puzzleInput) = 0;

    virtual int solvePartTwo(std::string& puzzleInput) = 0;
};
