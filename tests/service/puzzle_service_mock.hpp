// ReSharper disable CppClassCanBeFinal
#pragma once

#include <gmock/gmock.h>
#include "service/puzzle_service.hpp"

class PuzzleServiceMock : public PuzzleService {
public:
    explicit PuzzleServiceMock(Session session) : PuzzleService(session) {
        /* no-op */
    }

    MOCK_METHOD(std::string, readPuzzleInput, (int), (override));
};
