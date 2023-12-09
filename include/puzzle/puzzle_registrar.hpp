#pragma once

#include "puzzle_registry.hpp"
#include "service/puzzle_service.hpp"

template<int Day, typename PuzzleType>
class PuzzleRegistrar {
public:
    explicit PuzzleRegistrar(const std::string &title) {
        PuzzleRegistry::getInstance().registerPuzzle(Day, [](PuzzleService &service) -> std::unique_ptr<DayPuzzle> {
            return std::make_unique<PuzzleType>(service);
        }, title);
    }
};