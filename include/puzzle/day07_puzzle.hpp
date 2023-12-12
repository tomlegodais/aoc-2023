#pragma once

#include "day_puzzle.hpp"
#include "puzzle_registrar.hpp"

class [[maybe_unused]] Day07Puzzle final : public DayPuzzle
{
public:
    explicit Day07Puzzle(const PuzzleService& puzzleService) : DayPuzzle(puzzleService)
    {
        /* no-op */
    }

    int solvePartOne(std::string& puzzleInput) override;

    int solvePartTwo(std::string& puzzleInput) override;

private:
    [[maybe_unused]] static PuzzleRegistrar<7, Day07Puzzle> registrar;
};
