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

    static Session fromValue(const std::string &value) {
        return Session(value);
    }

    const std::string &getValue() {
        return value;
    }
};