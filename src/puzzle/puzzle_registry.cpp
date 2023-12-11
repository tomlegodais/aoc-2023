#include "puzzle/puzzle_registry.hpp"
#include <stdexcept>

std::unique_ptr<DayPuzzle> PuzzleRegistry::createPuzzle(int day, PuzzleService& puzzleService) const
{
    const auto it = info_.find(day);
    if (it == info_.end())
    {
        throw std::runtime_error("No puzzle registered for day " + std::to_string(day));
    }
    return it->second.constructor(puzzleService);
}
