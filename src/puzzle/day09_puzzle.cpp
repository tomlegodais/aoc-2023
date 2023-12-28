#include "puzzle/day_puzzle.hpp"
#include <sstream>

using Sequence = std::vector<int>;
using Sequences = std::vector<Sequence>;

Sequences parse_sequences(const std::vector<std::string> &input) {
    Sequences sequences;
    for (const auto &line: input) {
        Sequence sequence;
        std::istringstream iss(line);
        int value;

        while (iss >> value) {
            sequence.push_back(value);
        }

        sequences.push_back(sequence);
    }

    return sequences;
}

std::pair<Sequence, bool> get_distances(const Sequence &sequence) {
    Sequence distances;
    for (size_t i = 0; i < sequence.size() - 1; ++i) {
        distances.push_back(sequence[i + 1] - sequence[i]);
    }

    auto all_equal = std::ranges::adjacent_find(distances, std::not_equal_to()) == distances.end();
    return {distances, all_equal};
}

int calculate_next_value(const Sequence &original_sequence) {
    Sequences extrapolated;
    auto [distances, equal_distances] = get_distances(original_sequence);
    extrapolated.push_back(distances);

    while (!equal_distances) {
        std::tie(distances, equal_distances) = get_distances(distances);
        extrapolated.push_back(distances);
    }

    for (auto rit = extrapolated.rbegin() + 1; rit != extrapolated.rend(); ++rit) {
        auto &current_vector = *rit;
        auto &previous_vector = *std::prev(rit);

        current_vector.push_back(current_vector.back() + previous_vector.back());
    }

    return original_sequence.back() + extrapolated.front().back();
}

int calculate_previous_value(const Sequence &original_sequence) {
    Sequences extrapolated;
    auto [distances, equal_distance] = get_distances(original_sequence);
    extrapolated.push_back(distances);

    while (!equal_distance) {
        std::tie(distances, equal_distance) = get_distances(distances);
        extrapolated.push_back(distances);
    }

    extrapolated.back().insert(extrapolated.back().begin(), extrapolated.back().front());
    for (auto rit = extrapolated.rbegin(); rit != extrapolated.rend() - 1; ++rit) {
        auto &next_vector = *rit;
        auto &current_vector = *std::next(rit);

        current_vector.insert(current_vector.begin(), current_vector.front() - next_vector.front());
    }

    return original_sequence.front() - extrapolated.front().front();
}

template<>
PuzzleResult DayPuzzle<9>::solve_part_one(PuzzleService &, const std::vector<std::string> &puzzle_input) {
    const auto sequences = parse_sequences(puzzle_input);
    int sum = 0;
    for (auto &sequence: sequences) {
        sum += calculate_next_value(sequence);
    }

    return sum;
}

template<>
PuzzleResult DayPuzzle<9>::solve_part_two(PuzzleService &, const std::vector<std::string> &puzzle_input) {
    const auto sequences = parse_sequences(puzzle_input);
    int sum = 0;
    for (auto &sequence: sequences) {
        sum += calculate_previous_value(sequence);
    }

    return sum;
}

template<>
const char *DayPuzzle<9>::get_title() {
    return "Mirage Maintenance";
}