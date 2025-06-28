#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>

class Logger {
private:
    static std::string timestamp() {
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);
        std::tm buf;
#ifdef _WIN32
        localtime_s(&buf, &in_time_t);
#else
        localtime(&in_time, &buf);
#endif
        std::ostringstream oss;
        oss << std::put_time(&buf, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }

public:
    enum class Level { Info, Warning, Error };

    static void log(const std::string &message, Level level = Level::Info) {
        std::ostream &out = std::cout;
        out << "[" << timestamp() << "] ";
        switch (level) {
            case Level::Info:
                out << "[INFO] ";
                break;
            case Level::Warning:
                out << "[WARNING] ";
                break;
            case Level::Error:
                out << "[ERROR] ";
                break;
        }
        out << message << std::endl;
    }
};
