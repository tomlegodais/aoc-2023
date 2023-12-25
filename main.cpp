#include "puzzle/day_puzzle.hpp"
#include "service/puzzle_service.hpp"
#include "session/session.hpp"
#include "util/utils.hpp"
#include <iostream>
#include <limits>
#include <set>
#include <tuple>
#include <variant>

template<typename Seq>
struct PuzzleTuple;

template<int... Days>
struct PuzzleTuple<std::integer_sequence<int, Days...>> {
    using type = std::tuple<DayPuzzle<Days + 1>...>;
};

using PuzzleDays = std::make_integer_sequence<int, 8>;
using Puzzles = PuzzleTuple<PuzzleDays>::type;

template<typename Puzzle>
void print_puzzle() {
    std::cout << Puzzle::day << ". " << Puzzle::get_title() << std::endl;
}

template<std::size_t I = 0, typename... Tp>
std::enable_if_t<I == sizeof...(Tp), void>
list_puzzle(std::tuple<Tp...> &) {
    std::cout << std::endl;
}

template<std::size_t I = 0, typename... Tp>
std::enable_if_t < I<sizeof...(Tp)>
list_puzzle(std::tuple<Tp...> &t) {
    print_puzzle<std::tuple_element_t<I, std::tuple<Tp...>>>();
    list_puzzle<I + 1, Tp...>(t);
}

template<std::size_t I = 0, typename... Tp>
constexpr std::enable_if_t<I == sizeof...(Tp), std::set<int>>
get_puzzle_days(std::tuple<Tp...> &) {
    return {};
}

template<std::size_t I = 0, typename... Tp>
constexpr std::enable_if_t < I<sizeof...(Tp), std::set<int>>
get_puzzle_days(std::tuple<Tp...> &t) {
    std::set<int> days = get_puzzle_days<I + 1>(t);
    days.insert(std::tuple_element_t<I, std::tuple<Tp...>>::day);
    return days;
}

template<int Day>
void print_result(PuzzleService &puzzle_service,
                  const std::vector<std::string> &puzzle_input,
                  PuzzleResult (DayPuzzle<Day>::*solve)(PuzzleService &, const std::vector<std::string> &),
                  const std::string &part) {
    const auto [result, time] = utils::measure_execution_time([&] {
        return (DayPuzzle<Day>().*solve)(puzzle_service, puzzle_input);
    });

    std::visit([&](auto &&arg) { std::cout << part << ": " << arg; }, result);
    std::cout << " (" << time << "ms)" << std::endl;
}

template<int Day>
void solve_puzzle(PuzzleService &puzzle_service) {
    std::cout << std::endl
              << "Solving puzzle for day " << Day << ", please wait..." << std::endl;

    const auto puzzle_input = puzzle_service.read_puzzle_input(Day);
    constexpr PuzzleResult (DayPuzzle<Day>::*solves[])(PuzzleService &, const std::vector<std::string> &) = {
        &DayPuzzle<Day>::solve_part_one,
        &DayPuzzle<Day>::solve_part_two
    };

    for (const auto &solve: solves) {
        print_result(puzzle_service, puzzle_input, solve, solve == solves[0] ? "Part One" : "Part Two");
    }
}

template<std::size_t I = 0, typename... Tp>
std::enable_if_t<I == sizeof...(Tp), void>
solve_puzzle_for_day(std::tuple<Tp...> &, int, PuzzleService &) {
    /* no-op */
}

template<std::size_t I = 0, typename... Tp>
std::enable_if_t < I<sizeof...(Tp), void>
solve_puzzle_for_day(std::tuple<Tp...> &puzzles, int day, PuzzleService &puzzle_service) {
    if constexpr (I < sizeof...(Tp)) {
        if (std::tuple_element_t<I, std::tuple<Tp...>>::day == day) {
            solve_puzzle<std::tuple_element_t<I, std::tuple<Tp...>>::day>(puzzle_service);
            return;
        }
        solve_puzzle_for_day<I + 1, Tp...>(puzzles, day, puzzle_service);
    }
}

int prompt_for_day(const std::set<int> &days) {
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
        list_puzzle(puzzles);

        const auto puzzle_days = get_puzzle_days(puzzles);
        const int day = prompt_for_day(puzzle_days);
        if (day == -1) {
            return 0;
        }

        auto session = Session::init(".session");
        auto puzzle_service = PuzzleService(session);

        solve_puzzle_for_day(puzzles, day, puzzle_service);
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}
