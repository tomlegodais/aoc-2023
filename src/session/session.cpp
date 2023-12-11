#include <fstream>
#include <stdexcept>
#include "session/session.hpp"

Session Session::init(const std::string& fileName) {
    std::string sessionValue;
    if (std::ifstream file(fileName.c_str()); file.is_open()) {
        getline(file, sessionValue);
        file.close();
    } else {
        throw std::runtime_error("Unable to open session file in path: \"" + fileName + "\"\n" +
                                 "Please create a file named \"" + fileName + "\" and put your session value in it.");
    }

    if (sessionValue.empty()) {
        throw std::runtime_error(
            "Session value is empty, please put your session value in the file \"" + fileName + "\"");
    }

    return Session(sessionValue);
}
