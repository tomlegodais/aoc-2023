#include "puzzle/day_puzzle.hpp"
#include <list>
#include <unordered_map>

struct Point {
    int x, y;
};

enum class Direction {
    NORTH,
    EAST,
    SOUTH,
    WEST
};

struct Pipe {
    char symbol;
    std::vector<Direction> connections;
};

std::unordered_map<char, Pipe> pipes = {
        {'|', {'|', {Direction::NORTH, Direction::SOUTH}}},
        {'-', {'-', {Direction::EAST, Direction::WEST}}},
        {'L', {'L', {Direction::SOUTH, Direction::EAST}}},
        {'J', {'J', {Direction::SOUTH, Direction::WEST}}},
        {'7', {'7', {Direction::NORTH, Direction::WEST}}},
        {'F', {'F', {Direction::NORTH, Direction::EAST}}},
        {'S', {'S', {Direction::NORTH, Direction::EAST, Direction::SOUTH, Direction::WEST}}}};

bool operator==(const Point &a, const Point &b) {
    return a.x == b.x && a.y == b.y;
}

template<>
struct std::hash<Point> {
    size_t operator()(const Point &p) const noexcept {
        return hash<int>()(p.x) ^ hash<int>()(p.y);
    }
};

using Graph = std::unordered_map<Point, std::list<Point>>;

bool is_pipe(char tile) {
    return true;
}

void add_edge(Graph &graph, Point a, Point b) {
}

bool has_direction(const std::vector<Direction> &connections, Direction dir) {
    return std::find(connections.begin(), connections.end(), dir) != connections.end();
}

bool is_connectable(char a, char b) {

    return false;
}

Graph parse_graph(const std::vector<std::string> &input) {
    Graph graph;

    for (int y = 0; y < input.size(); y++) {
        for (int x = 0; x < input[y].size(); x++) {
        }
    }

    return graph;
}

template<>
PuzzleResult DayPuzzle<10>::solve_part_one(PuzzleService &, const std::vector<std::string> &puzzle_input) {
    const auto graph = parse_graph(puzzle_input);
    return 0;
}

template<>
PuzzleResult DayPuzzle<10>::solve_part_two(PuzzleService &, const std::vector<std::string> &puzzle_input) {
    return 0;
}

template<>
const char *DayPuzzle<10>::get_title() {
    return "Pipe Maze";
}
