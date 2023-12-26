#include "puzzle/day_puzzle.hpp"
#include "util/utils.hpp"
#include <map>
#include <memory>
#include <numeric>
#include <regex>

struct Node {
    std::string value;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;

    explicit Node(std::string value) : value(std::move(value)), left(nullptr), right(nullptr) {}
};

class NodeList {
public:
    explicit NodeList(const std::vector<std::string> &puzzle_input) {
        build_nodes(puzzle_input);
    }

    std::shared_ptr<Node> get_node(const std::string &value) {
        if (!nodes_.contains(value)) {
            nodes_[value] = std::make_shared<Node>(value);
        }
        return nodes_[value];
    }

    void build_nodes(const std::vector<std::string> &puzzle_input) {
        std::vector<std::tuple<std::string, std::string, std::string>> connections;
        const std::regex regex("([A-Z0-9]{3}) = \\(([A-Z0-9]{3}), ([A-Z0-9]{3})\\)");
        for (const std::string &line: puzzle_input) {
            if (std::smatch match; std::regex_match(line, match, regex)) {
                const std::shared_ptr<Node> node = get_node(match[1]);
                connections.emplace_back(node->value, match[2], match[3]);
            }
        }

        for (const auto &[current, left, right]: connections) {
            const auto current_node = get_node(current);
            current_node->left = get_node(left);
            current_node->right = get_node(right);
        }
    }

    std::vector<std::shared_ptr<Node>> find_starting_nodes() {
        std::vector<std::shared_ptr<Node>> starting_nodes;
        for (const auto &[key, value]: nodes_) {
            if (key.ends_with("A")) starting_nodes.push_back(value);
        }
        return starting_nodes;
    }

private:
    std::map<std::string, std::shared_ptr<Node>> nodes_;
};

std::vector<char> parse_instructions(const std::vector<std::string> &puzzle_input) {
    std::vector<char> instructions;
    for (const char c: puzzle_input[0]) {
        instructions.push_back(c);
    }
    return instructions;
}

int cycle_length(std::shared_ptr<Node> node, const std::vector<char> &instructions) {
    int length = 0;
    size_t instruction_index = 0;

    while (!node->value.ends_with("Z")) {
        node = (instructions[instruction_index] == 'L') ? node->left : node->right;
        instruction_index = (instruction_index + 1) % instructions.size();
        length++;
    }

    return length;
}

long long lcm(const long long a, const long long b) {
    return a / std::gcd(a, b) * b;
}

template<>
PuzzleResult DayPuzzle<8>::solve_part_one(PuzzleService &, const std::vector<std::string> &puzzle_input) {
    NodeList node_list(puzzle_input);
    const std::vector<char> instructions = parse_instructions(puzzle_input);
    return cycle_length(node_list.get_node("AAA"), instructions);
}

template<>
PuzzleResult DayPuzzle<8>::solve_part_two(PuzzleService &, const std::vector<std::string> &puzzle_input) {
    NodeList node_list(puzzle_input);
    const std::vector<char> instructions = parse_instructions(puzzle_input);

    const auto starting_nodes = node_list.find_starting_nodes();
    std::vector<long long> cycle_lengths;

    cycle_lengths.reserve(starting_nodes.size());
    for (auto &node: starting_nodes) {
        cycle_lengths.push_back(cycle_length(node, instructions));
    }

    long long total_lcm = cycle_lengths[0];
    for (int i = 1; i < cycle_lengths.size(); i++) {
        total_lcm = lcm(total_lcm, cycle_lengths[i]);
    }

    return total_lcm;
}

template<>
const char *DayPuzzle<8>::get_title() {
    return "Haunted Wasteland";
}