#include "puzzle/day07_puzzle.hpp"
#include "puzzle/puzzle_registrar.hpp"
#include "util/string_utils.hpp"
#include <algorithm>
#include <ranges>

class CardMappingStrategy {
protected:
    ~CardMappingStrategy() = default;

public:
    explicit CardMappingStrategy(std::unordered_map<char, std::pair<std::string, int>> card_mapping)
        : card_mapping_(std::move(card_mapping)) {}

    [[nodiscard]] virtual std::pair<std::string, int> getCardProperties(const char ch) const {
        if (const auto it = card_mapping_.find(ch); it != card_mapping_.end())
            return it->second;

        return {std::string(1, ch), ch - '0'};
    }

private:
    std::unordered_map<char, std::pair<std::string, int>> card_mapping_;
};

class PartOneMappingStrategy final : public CardMappingStrategy {
public:
    PartOneMappingStrategy() : CardMappingStrategy({{'A', {"Ace", 14}},
                                                    {'K', {"King", 13}},
                                                    {'Q', {"Queen", 12}},
                                                    {'J', {"Jack", 11}},
                                                    {'T', {"10", 10}}}) {}
};

class PartTwoMappingStrategy final : public CardMappingStrategy {
public:
    PartTwoMappingStrategy() : CardMappingStrategy({{'A', {"Ace", 14}},
                                                    {'K', {"King", 13}},
                                                    {'Q', {"Queen", 12}},
                                                    {'T', {"10", 10}},
                                                    {'J', {"Joker", 1}}}) {}
};

struct Card {
    std::string value_;
    int strength_;

    explicit Card(const char ch, const CardMappingStrategy &strategy) {
        const auto [card_value, card_strength] = strategy.getCardProperties(ch);
        value_ = card_value;
        strength_ = card_strength;
    }
};

struct Hand {
    std::vector<Card> cards_;
    int bid_;

    explicit Hand(const std::string &str, const CardMappingStrategy &strategy) {
        for (int i = 0; i < 5; i++) {
            cards_.emplace_back(str[i], strategy);
        }
        bid_ = std::stoi(str.substr(6));
    }
};

enum class HandType {
    FiveOfAKind,
    FourOfAKind,
    FullHouse,
    ThreeOfAKind,
    TwoPair,
    OnePair,
    HighCard
};

class PokerHand : public Hand {
    HandType type_;

    [[nodiscard]] HandType determineHandType() const {
        std::unordered_map<char, int> frequency;
        int joker_count = 0;
        for (const auto &card: cards_) {
            if (card.value_ == "Joker") {
                joker_count++;
            } else {
                frequency[card.value_[0]]++;
            }
        }

        for (int j = 0; j < joker_count; ++j) {

            if (auto best_use = std::ranges::max_element(frequency,
                                                         [](const auto &a, const auto &b) { return a.second < b.second; });
                best_use != frequency.end()) {
                best_use->second++;
            } else {
                frequency['*'] = 1;
            }
        }

        int pairs = 0, triplets = 0, quads = 0, quints = 0;
        for (const auto &val: frequency | std::views::values) {
            if (val == 2) pairs++;
            else if (val == 3)
                triplets++;
            else if (val == 4)
                quads++;
            else if (val == 5)
                quints++;
        }

        if (quints == 1) return HandType::FiveOfAKind;
        if (quads == 1) return HandType::FourOfAKind;
        if (triplets == 1 && pairs == 1) return HandType::FullHouse;
        if (triplets == 1) return HandType::ThreeOfAKind;
        if (pairs == 2) return HandType::TwoPair;
        if (pairs == 1) return HandType::OnePair;
        return HandType::HighCard;
    }

public:
    using Hand::Hand;

    explicit PokerHand(const std::string &str, const CardMappingStrategy &strategy) : Hand(str, strategy) {
        type_ = this->determineHandType();
    }

    bool operator<(const PokerHand &other) const {
        if (type_ != other.type_)
            return type_ > other.type_;

        for (int i = 0; i < cards_.size(); ++i) {
            if (cards_[i].strength_ != other.cards_[i].strength_)
                return cards_[i].strength_ < other.cards_[i].strength_;
        }
        return false;
    }
};

int solveWithStrategy(const std::string &puzzle_input, const CardMappingStrategy &strategy) {
    std::vector<PokerHand> poker_hands;
    for (const auto &line: StringUtils::splitOnNewline(puzzle_input)) {
        poker_hands.emplace_back(line, strategy);
    }

    std::sort(poker_hands.begin(), poker_hands.end());

    int total = 0;
    for (int i = 0; i < poker_hands.size(); ++i) {
        total += poker_hands[i].bid_ * (i + 1);
    }

    return total;
}

int Day07Puzzle::solvePartOne(std::string &puzzle_input) {
    const PartOneMappingStrategy strategy;
    return solveWithStrategy(puzzle_input, strategy);
}

int Day07Puzzle::solvePartTwo(std::string &puzzle_input) {
    const PartTwoMappingStrategy strategy;
    return solveWithStrategy(puzzle_input, strategy);
}


[[maybe_unused]] PuzzleRegistrar<7, Day07Puzzle> Day07Puzzle::registrar_("Camel Cards");
