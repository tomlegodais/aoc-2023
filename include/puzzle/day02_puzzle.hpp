#pragma once

#include "day_puzzle.hpp"
#include "puzzle_registrar.hpp"

class [[maybe_unused]] Day02Puzzle : public DayPuzzle {
public:
    explicit Day02Puzzle(const PuzzleService &puzzleService) : DayPuzzle(puzzleService) {};

    int solvePartOne(std::string &puzzleInput) override;

    int solvePartTwo(std::string &puzzleInput) override;

private:
    [[maybe_unused]] static PuzzleRegistrar<2, Day02Puzzle> registrar;
};