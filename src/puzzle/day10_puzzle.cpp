#include "puzzle/day_puzzle.hpp"
#include <iostream>
#include <optional>
#include <set>
#include <unordered_map>

class Vector2 {
public:
    int x = 0, y = 0;

    explicit Vector2(const int x, const int y) : x(x), y(y) {}

    Vector2 operator+(const Vector2 &rhs) const {
        return Vector2(x + rhs.x, y + rhs.y);
    }

    Vector2 operator-() const {
        return Vector2(-x, -y);
    }

    Vector2 operator-(const Vector2 &rhs) const {
        return Vector2(x - rhs.x, y - rhs.y);
    }

    bool operator<(const Vector2 &other) const {
        if (x == other.x) return y < other.y;
        return x < other.x;
    }

    bool operator==(const Vector2 &other) const {
        return x == other.x && y == other.y;
    }

    friend std::ostream &operator<<(std::ostream &os, const Vector2 &vector) {
        os << "(" << vector.x << ", " << vector.y << ")";
        return os;
    }
};

const Vector2 NORTH(0, -1),
        EAST(1, 0),
        SOUTH(0, 1),
        WEST(-1, 0);

const std::unordered_map<char, std::set<Vector2>> DIRECTIONS = {
        {'|', {NORTH, SOUTH}},
        {'-', {EAST, WEST}},
        {'L', {NORTH, EAST}},
        {'J', {NORTH, WEST}},
        {'7', {SOUTH, WEST}},
        {'F', {SOUTH, EAST}},
};

class PipeMaze {
public:
    static PipeMaze parse(const std::vector<std::string> &input) {
        const int height = input.size();
        const int width = input[0].size();
        auto tiles = std::make_unique<char[]>(width * height);
        std::optional<Vector2> start_pos;

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                const auto tile = input[y][x];
                if (tile == 'S') start_pos = Vector2(x, y);
                tiles[y * width + x] = tile;
            }
        }

        if (!start_pos.has_value()) throw std::runtime_error("No start position found");
        return PipeMaze(height, width, std::move(tiles), start_pos.value());
    }

    explicit PipeMaze(const int height, const int width, std::unique_ptr<char[]> tiles, const Vector2 &start_pos) : height(height),
                                                                                                                    width(width),
                                                                                                                    tiles(std::move(tiles)),
                                                                                                                    start_pos(start_pos) {
        const auto start_tile = infer_start_tile();
        this->set_tile(start_pos, start_tile);
    }

    [[nodiscard]] std::set<Vector2> traverse() const {
        std::set<Vector2> visited;
        Vector2 pos = start_pos;

    traversal:
        while (true) {
            const auto tile = get_tile(pos);
            visited.insert(pos);

            bool start_adjacent = false;
            for (const auto &dir: get_directions(tile)) {
                if (const auto next = pos + dir; !visited.contains(next)) {
                    pos = next;
                    goto traversal;
                } else if (next == start_pos) {
                    start_adjacent = true;
                }
            }

            if (start_adjacent) break;
        }

        return visited;
    }

private:
    int height, width;
    std::unique_ptr<char[]> tiles;
    Vector2 start_pos;

    void set_tile(const Vector2 &pos, const char tile) const {
        tiles[pos.y * width + pos.x] = tile;
    }

    [[nodiscard]] char get_tile(const Vector2 &pos) const {
        return tiles[pos.y * width + pos.x];
    }

    [[nodiscard]] char infer_start_tile() const {
        std::set<Vector2> connected_directions;
        for (const auto &dir: {NORTH, EAST, SOUTH, WEST}) {
            if (!is_connected(start_pos, dir)) continue;
            connected_directions.insert(dir);
        }

        std::optional<char> tile_type;
        for (const auto &[key, value]: DIRECTIONS) {
            if (value == connected_directions) tile_type = key;
        }

        if (!tile_type.has_value()) throw std::runtime_error("Could not infer start tile type");
        return tile_type.value();
    }

    [[nodiscard]] static std::set<Vector2> get_directions(const char tile) {
        const auto directions = DIRECTIONS.find(tile);
        if (directions == DIRECTIONS.end()) return {};
        return directions->second;
    }

    [[nodiscard]] bool is_connected(const Vector2 &pos, const Vector2 &dir) const {
        return get_directions(get_tile(pos + dir)).contains(-dir);
    }
};

template<>
PuzzleResult DayPuzzle<10>::solve_part_one(PuzzleService &, const std::vector<std::string> &puzzle_input) {
    const auto pipe_maze = PipeMaze::parse(puzzle_input);
    const auto visited = pipe_maze.traverse();
    return static_cast<int>(visited.size() + 1) / 2;
}

template<>
PuzzleResult DayPuzzle<10>::solve_part_two(PuzzleService &, const std::vector<std::string> &) {
    return 0;
}

template<>
const char *DayPuzzle<10>::get_title() {
    return "Pipe Maze";
}
