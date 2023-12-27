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

    for (int i = extrapolated.size() - 2; i >= 0; --i) {
        extrapolated[i].push_back(extrapolated[i].back() + extrapolated[i + 1].back());
    }

    return original_sequence.back() + extrapolated[0].back();
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
PuzzleResult DayPuzzle<9>::solve_part_two(PuzzleService &, const std::vector<std::string> &) {
    return 0;
}

template<>
const char *DayPuzzle<9>::get_title() {
    return "Mirage Maintenance";
}