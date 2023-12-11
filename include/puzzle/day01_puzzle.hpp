#pragma once

#include "day_puzzle.hpp"
#include "puzzle_registrar.hpp"

class [[maybe_unused]] Day01Puzzle final : public DayPuzzle
{
public:
    explicit Day01Puzzle(const PuzzleService& puzzleService) : DayPuzzle(puzzleService)
    {
        /* no-op */
    }

    int solvePartOne(std::string& puzzleInput) override;

    int solvePartTwo(std::string& puzzleInput) override;

private:
    [[maybe_unused]] static PuzzleRegistrar<1, Day01Puzzle> registrar;
};
