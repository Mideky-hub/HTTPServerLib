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

    constexpr const char* log_level_str(log_level level) {
        switch (level) {
            case INFO: return "INFO";
            case WARN: return "WARN";
            case ERROR: return "ERROR";
            case FATAL: return "FATAL";
            case DEBUG: return "DEBUG";
            default: return "UNKNOWN";
        }
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