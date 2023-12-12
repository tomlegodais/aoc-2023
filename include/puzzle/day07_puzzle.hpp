#pragma once

#include "day_puzzle.hpp"
#include "puzzle_registrar.hpp"

class [[maybe_unused]] Day07Puzzle final : public DayPuzzle {
public:
    explicit Day07Puzzle(const PuzzleService &puzzle_service) : DayPuzzle(puzzle_service) {}

    int solvePartOne(std::string &puzzle_input) override;

    int solvePartTwo(std::string &puzzle_input) override;

private:
    [[maybe_unused]] static PuzzleRegistrar<7, Day07Puzzle> registrar_;
};
