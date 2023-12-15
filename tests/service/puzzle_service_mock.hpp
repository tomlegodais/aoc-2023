// ReSharper disable CppClassCanBeFinal
#pragma once

#include "service/puzzle_service.hpp"
#include <gmock/gmock.h>

class PuzzleServiceMock : public PuzzleService {
public:
    explicit PuzzleServiceMock(Session session) : PuzzleService(session) {}

    MOCK_METHOD(std::vector<std::string>, readPuzzleInput, (int), (override));
};
