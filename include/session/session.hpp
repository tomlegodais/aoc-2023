#pragma once

#include <string>
#include <utility>

class Session {
private:
    std::string value;

    explicit Session(std::string value) : value(std::move(value)) {};

public:
    ~Session() = default;

    static Session init(const std::string &fileName);

    const std::string &getValue() {
        return value;
    }
};