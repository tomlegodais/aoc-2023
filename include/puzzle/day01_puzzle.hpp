#pragma once

#include "day_puzzle.hpp"
#include "puzzle_registrar.hpp"

class [[maybe_unused]] Day01Puzzle final : public DayPuzzle {
public:
    explicit Day01Puzzle(const PuzzleService &puzzle_service) : DayPuzzle(puzzle_service) {}

    int solvePartOne(std::string &puzzle_input) override;

    int solvePartTwo(std::string &puzzle_input) override;

private:
    [[maybe_unused]] static PuzzleRegistrar<1, Day01Puzzle> registrar_;
};
