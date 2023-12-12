#pragma once

#include "day_puzzle.hpp"
#include <functional>
#include <map>
#include <memory>
#include <utility>

using PuzzleConstructor = std::function<std::unique_ptr<DayPuzzle>(PuzzleService &)>;

struct PuzzleInfo {
    PuzzleConstructor constructor;
    std::string title;
};

class PuzzleRegistry {
public:
    static PuzzleRegistry &getInstance() {
        static PuzzleRegistry instance;
        return instance;
    }

    void registerPuzzle(const int day, PuzzleConstructor constructor, const std::string &title) {
        info_[day] = {std::move(constructor), title};
    }

    std::unique_ptr<DayPuzzle> createPuzzle(int day, PuzzleService &puzzle_service) const;

    [[nodiscard]] const std::map<int, PuzzleInfo> &getPuzzleInfo() const {
        return info_;
    }

private:
    std::map<int, PuzzleInfo> info_;
};
