#include "puzzle/day_puzzle.hpp"
#include "service/puzzle_service.hpp"
#include "session/session.hpp"
#include "util/utils.hpp"
#include <iostream>
#include <limits>
#include <set>

template<typename Seq>
struct PuzzleTuple;

template<int... Days>
struct PuzzleTuple<std::integer_sequence<int, Days...>> {
    using type = std::tuple<DayPuzzle<Days + 1>...>;
};

using PuzzleDays = std::make_integer_sequence<int, 7>;
using Puzzles = PuzzleTuple<PuzzleDays>::type;

template<typename Puzzle>
void printPuzzle() {
    std::cout << Puzzle::day << ". " << Puzzle::getTitle() << std::endl;
}

template<std::size_t I = 0, typename... Tp>
std::enable_if_t<I == sizeof...(Tp), void>
listPuzzle(std::tuple<Tp...> &) {
    std::cout << std::endl;
}

template<std::size_t I = 0, typename... Tp>
std::enable_if_t < I<sizeof...(Tp)>
listPuzzle(std::tuple<Tp...> &t) {
    printPuzzle<std::tuple_element_t<I, std::tuple<Tp...>>>();
    listPuzzle<I + 1, Tp...>(t);
}

template<std::size_t I = 0, typename... Tp>
constexpr std::enable_if_t<I == sizeof...(Tp), std::set<int>>
getPuzzleDays(std::tuple<Tp...> &) {
    return {};
}

template<std::size_t I = 0, typename... Tp>
constexpr std::enable_if_t < I<sizeof...(Tp), std::set<int>>
getPuzzleDays(std::tuple<Tp...> &t) {
    std::set<int> days = getPuzzleDays<I + 1>(t);
    days.insert(std::tuple_element_t<I, std::tuple<Tp...>>::day);
    return days;
}

template<int Day>
void solvePuzzle(PuzzleService &puzzle_service) {
    std::cout << std::endl
              << "Solving puzzle for day " << Day << ", please wait..." << std::endl;

    const auto puzzle_input = puzzle_service.readPuzzleInput(Day);
    const auto [partOneResult, partOneTime] = utils::measureExecutionTime([&] {
        return DayPuzzle<Day>::solvePartOne(puzzle_service, puzzle_input);
    });

    const auto [partTwoResult, partTwoTime] = utils::measureExecutionTime([&] {
        return DayPuzzle<Day>::solvePartTwo(puzzle_service, puzzle_input);
    });

    std::cout << "Part One: " << partOneResult << ", took " << partOneTime << " milliseconds" << std::endl;
    std::cout << "Part Two: " << partTwoResult << ", took " << partTwoTime << " milliseconds" << std::endl;
}

template<std::size_t I = 0, typename... Tp>
std::enable_if_t<I == sizeof...(Tp), void>
solvePuzzleForDay(std::tuple<Tp...> &, int, PuzzleService &) {
    /* no-op */
}

template<std::size_t I = 0, typename... Tp>
std::enable_if_t < I<sizeof...(Tp), void>
solvePuzzleForDay(std::tuple<Tp...> &puzzles, int day, PuzzleService &puzzle_service) {
    if constexpr (I < sizeof...(Tp)) {
        if (std::tuple_element_t<I, std::tuple<Tp...>>::day == day) {
            solvePuzzle<std::tuple_element_t<I, std::tuple<Tp...>>::day>(puzzle_service);
            return;
        }
        solvePuzzleForDay<I + 1, Tp...>(puzzles, day, puzzle_service);
    }
}

int promptForDay(const std::set<int> &days) {
    int day;

    while (true) {
        std::cout << "Enter the day you would like to solve (-1 to exit): ";
        std::cin >> day;

        if (day == -1) return 0;
        if (!std::cin.fail() && days.contains(day)) return day;

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid option. Please try again." << std::endl
                  << std::endl;
    }
}


int main() {
    try {
        std::cout << "Advent of Code 2023" << std::endl;
        std::cout << "===================" << std::endl;

        Puzzles puzzles;
        listPuzzle(puzzles);

        const auto puzzle_days = getPuzzleDays(puzzles);
        const int day = promptForDay(puzzle_days);
        if (day == -1) {
            return 0;
        }

        auto session = Session::init(".session");
        auto puzzle_service = PuzzleService(session);

        solvePuzzleForDay(puzzles, day, puzzle_service);
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}
