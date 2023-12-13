#include "puzzle/puzzle_registry.hpp"
#include "service/puzzle_service.hpp"
#include "session/session.hpp"
#include "util/time_utils.hpp"
#include <iostream>
#include <limits>

int promptForDay(const std::map<int, PuzzleInfo> &puzzleInfo) {
    int day;

    while (true) {
        std::cout << "Enter the day you would like to solve (-1 to exit): ";
        std::cin >> day;

        if (day == -1) {
            return -1;
        }

        if (std::cin.fail() || !puzzleInfo.contains(day)) {
            std::cout << "The day you entered is invalid, please try again." << std::endl
                      << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        return day;
    }
}

void solvePuzzle(const int day, PuzzleService &puzzleService) {
    std::cout << std::endl
              << "Solving puzzle for day " << day << ", please wait..." << std::endl;

    const auto puzzle = PuzzleRegistry::getInstance().createPuzzle(day, puzzleService);
    auto puzzleInput = puzzleService.readPuzzleInput(day);

    const auto [partOneResult, partOneTime] = TimeUtils::measureExecutionTime([&] {
        return puzzle->solvePartOne(puzzleInput);
    });
    std::cout << "Part One: " << partOneResult << ", took " << partOneTime << " milliseconds" << std::endl;

    const auto [partTwoResult, partTwoTime] = TimeUtils::measureExecutionTime([&] {
        return puzzle->solvePartTwo(puzzleInput);
    });
    std::cout << "Part Two: " << partTwoResult << ", took " << partTwoTime << " milliseconds" << std::endl;
}

int main() {
    try {
        const auto puzzleInfo = PuzzleRegistry::getInstance().getPuzzleInfo();
        std::cout << "Advent of Code 2023" << std::endl;
        std::cout << "===================" << std::endl;

        for (const auto &[fst, snd]: puzzleInfo) {
            std::cout << fst << ". Day " << fst << " (" << snd.title << ")" << std::endl;
            if (fst == puzzleInfo.size()) {
                std::cout << std::endl;
            }
        }

        const int day = promptForDay(puzzleInfo);
        if (day == -1) {
            return 1;
        }

        auto session = Session::init(".session");
        auto puzzleService = PuzzleService(session);

        solvePuzzle(day, puzzleService);
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}
