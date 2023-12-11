#pragma once

#include "day_puzzle.hpp"
#include "puzzle_registrar.hpp"

class [[maybe_unused]] Day02Puzzle final : public DayPuzzle
{
public:
    explicit Day02Puzzle(const PuzzleService& puzzleService) : DayPuzzle(puzzleService)
    {
        /* no-op */
    }

    int solvePartOne(std::string& puzzleInput) override;

    int solvePartTwo(std::string& puzzleInput) override;

private:
    static std::vector<std::string> parseGroups(const std::string& line);

    static std::map<std::string, int> countColors(const std::string& group);

    static bool isGroupValid(const std::string& group);

    static std::vector<int> getHighestValues(const std::map<std::string, std::vector<int>>& totalCounts);

    [[maybe_unused]] static PuzzleRegistrar<2, Day02Puzzle> registrar;
};
