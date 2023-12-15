#pragma once

#include "session/session.hpp"
#include <vector>

class PuzzleService {
public:
    explicit PuzzleService(Session &session) : session_(session) {}

    virtual ~PuzzleService() = default;

    virtual std::vector<std::string> readPuzzleInput(int day);

private:
    Session &session_;
};
