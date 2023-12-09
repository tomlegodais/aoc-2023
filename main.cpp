#include <iostream>
#include "session/session.hpp"
#include "puzzle/puzzle_registry.hpp"
#include "service/puzzle_service.hpp"

int promptForDay(const std::map<int, PuzzleInfo> &puzzleInfo) {
    int day;

    while (true) {
        std::cout << "Enter the day you would like to solve (-1 to exit): ";
        std::cin >> day;

        if (day == -1) {
            return -1;
        }

        if (std::cin.fail() || puzzleInfo.find(day) == puzzleInfo.end()) {
            std::cout << "The day you entered is invalid, please try again." << std::endl << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        return day;
    }
}

void solvePuzzle(int day, PuzzleService &puzzleService) {
    std::cout << std::endl << "Solving puzzle for day " << day << ", please wait..." << std::endl;

    auto puzzle = PuzzleRegistry::getInstance().createPuzzle(day, puzzleService);
    auto puzzleInput = puzzleService.readPuzzleInput(day);

    std::cout << "Part one: " << puzzle->solvePartOne(puzzleInput) << std::endl;
    std::cout << "Part two: " << puzzle->solvePartTwo(puzzleInput) << std::endl;
}

int main() {
    try {
        auto puzzleInfo = PuzzleRegistry::getInstance().getPuzzleInfo();
        std::cout << "Advent of Code 2023" << std::endl;
        std::cout << "===================" << std::endl;

        for (const auto &pair: puzzleInfo) {
            std::cout << pair.first << ". Day " << pair.first << " (" << pair.second.title << ")" << std::endl;
            if (pair.first == puzzleInfo.size()) {
                std::cout << std::endl;
            }
        }

        int day = promptForDay(puzzleInfo);
        if (day == -1) {
            return 0;
        }

        auto session = Session::init(".session");
        auto puzzleService = PuzzleService(session);

        solvePuzzle(day, puzzleService);
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
