#include "puzzle/day_puzzle.hpp"
#include "service/puzzle_service.hpp"
#include "session/session.hpp"
#include "util/utils.hpp"
#include <iostream>
#include <set>

using Puzzles = std::tuple<
        DayPuzzle<1>>;

template<typename Puzzle>
void printPuzzle() {
    std::cout << Puzzle::day << ". " << Puzzle::getTitle() << std::endl;
}

template<std::size_t I = 0, typename... Tp>
std::enable_if_t<I == sizeof...(Tp), void>
listPuzzle(std::tuple<Tp...> &) {}

template<std::size_t I = 0, typename... Tp>
        std::enable_if_t < I<sizeof...(Tp)> listPuzzle(std::tuple<Tp...> &t) {
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
    auto puzzleInput = puzzle_service.readPuzzleInput(Day);

    DayPuzzle<Day> day;

    const int partOne = day.solvePartOne(puzzle_service, puzzleInput);

    std::cout << "Part One: " << partOne << std::endl;
}

int main() {
    try {
        std::cout << "Advent of Code 2023" << std::endl;
        std::cout << "===================" << std::endl;

        Puzzles puzzles;
        listPuzzle(puzzles);

        // TODO: Implement a way to select a day

        auto session = Session::init(".session");
        auto puzzleService = PuzzleService(session);

        solvePuzzle<1>(puzzleService);
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}
