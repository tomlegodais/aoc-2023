#include "puzzle/day_puzzle.hpp"
#include <algorithm>
#include <queue>
#include <sstream>

struct ScratchCard {
    int id_;
    int match_count_;

    explicit ScratchCard(const int id, std::vector<int> &winning_numbers, std::vector<int> &scratch_numbers) {
        std::vector<int> intersections;
        std::ranges::set_intersection(winning_numbers, scratch_numbers,
                                      std::back_inserter(intersections));

        id_ = id;
        match_count_ = static_cast<int>(intersections.size());
    }
};

std::pair<std::vector<int>, std::vector<int>> extractNumbers(const std::string &str) {
    const auto start_of_numbers = str.find(':');
    if (start_of_numbers == std::string::npos) {
        return {};
    }

    auto number_str = str.substr(start_of_numbers + 1);
    const auto pipe_pos = number_str.find('|');
    if (pipe_pos == std::string::npos) {
        return {};
    }

    const auto left_part = number_str.substr(0, pipe_pos);
    const auto right_part = number_str.substr(pipe_pos + 1);
    const auto number_vector = [](const std::string &num_str) {
        std::istringstream iss(num_str);
        std::vector<int> numbers;

        int num;
        while (iss >> num) numbers.push_back(num);

        std::ranges::sort(numbers);
        return numbers;
    };

    const auto left_numbers = number_vector(left_part);
    const auto right_numbers = number_vector(right_part);
    return {left_numbers, right_numbers};
}

template<>
int DayPuzzle<4>::solvePartOne(PuzzleService &, const std::vector<std::string> &puzzle_input) {
    std::vector<ScratchCard> scratch_cards;
    for (int card_id = 1; card_id <= puzzle_input.size(); ++card_id) {
        auto [left_numbers, right_numbers] = extractNumbers(puzzle_input[card_id - 1]);
        scratch_cards.emplace_back(card_id, left_numbers, right_numbers);
    }

    int total_sum = 0;
    for (const auto &card: scratch_cards) {
        const int points = card.match_count_ != 0 ? 1 << card.match_count_ - 1 : 0;
        total_sum += points;
    }

    return total_sum;
}

template<>
int DayPuzzle<4>::solvePartTwo(PuzzleService &, const std::vector<std::string> &puzzle_input) {
    std::vector<ScratchCard> scratch_cards;
    std::queue<ScratchCard> card_queue;

    for (int card_id = 1; card_id <= puzzle_input.size(); ++card_id) {
        auto [left_numbers, right_numbers] = extractNumbers(puzzle_input[card_id - 1]);
        ScratchCard scratch_card(card_id, left_numbers, right_numbers);

        scratch_cards.emplace_back(scratch_card);
        card_queue.push(scratch_card);
    }

    int total_scratch_cards = 0;
    while (!card_queue.empty()) {
        const auto current_card = card_queue.front();
        card_queue.pop();
        total_scratch_cards++;

        for (int i = 1; i <= current_card.match_count_; ++i) {
            if (const auto next_card_id = current_card.id_ + i; next_card_id <= scratch_cards.size())
                card_queue.push(scratch_cards[next_card_id - 1]);
        }
    }

    return total_scratch_cards;
}

template<>
const char *DayPuzzle<4>::getTitle() {
    return "Scratchcards";
}