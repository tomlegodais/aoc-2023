#pragma once

#include "day_puzzle.hpp"
#include "puzzle_registrar.hpp"

class [[maybe_unused]] Day03Puzzle final : public DayPuzzle {
public:
    explicit Day03Puzzle(const PuzzleService &puzzle_service) : DayPuzzle(puzzle_service) {}

    int solvePartOne(std::vector<std::string> &puzzle_input) override;

    int solvePartTwo(std::vector<std::string> &puzzle_input) override;

private:
    [[maybe_unused]] static PuzzleRegistrar<3, Day03Puzzle> registrar_;
};
