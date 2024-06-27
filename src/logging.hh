#ifndef LOGGING_HH
#define LOGGING_HH

#include <iostream>
#include <string>
#include <array>

namespace logging {
    enum log_level {
    INFO,
    WARN,
    ERROR,
    FATAL,
    DEBUG,
    MAX
};

std::string log_level_str(log_level level) {
    static const std::array<std::string, MAX> logLevelStrings = {
        "INFO", "WARN", "ERROR", "FATAL", "DEBUG"
    };

    if (level >= INFO && level < MAX) {
        return logLevelStrings[level];
    }
    return "UNKNOWN";
}
}

namespace server{
    // To be implemented
}

namespace sys {
    void log(logging::log_level level, std::string message) {
        printf("[%s] %s\n", logging::log_level_str(level), message);
    }

    void exit(int code, std::string message) {
        log(logging::FATAL, message);
        std::exit(code);
    }
}

#endif // LOGGING_HH