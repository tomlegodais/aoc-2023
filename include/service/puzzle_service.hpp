#pragma once

#include "session/session.hpp"

class PuzzleService {
public:
    explicit PuzzleService(Session &session) : session_(session) {};

    virtual ~PuzzleService() = default;

    virtual std::string readPuzzleInput(int day);

private:
    Session &session_;
};