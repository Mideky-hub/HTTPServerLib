#ifndef LOGGING_HH
#define LOGGING_HH

// Standard libraries
#include <iostream>
#include <string>
#include <array>
#include <ctime>

// Best practice for logging system format:
// DATE : [LEVEL] MESSAGE 

namespace logging {
    enum log_level {
        LOG_INFO,
        LOG_WARN,
        LOG_ERROR,
        LOG_FATAL,
        LOG_DEBUG,
        MAX
    };

    constexpr const char* log_level_str(logging::log_level level) {
        switch (level) {
            case logging::LOG_INFO: return "INFO";
            case logging::LOG_WARN: return "WARN";
            case logging::LOG_ERROR: return "ERROR";
            case logging::LOG_FATAL: return "FATAL";
            case logging::LOG_DEBUG: return "DEBUG";
            default: return "UNKNOWN";
        }
    }
}

namespace server{
    // To be implemented
}

namespace sys {
    void log(logging::log_level level, std::string message) {
        printf("[%s] %s\n", logging::log_level_str(level), message.c_str());
    }

    void exit(int code, std::string message) {
        sys::log(logging::LOG_FATAL, message);
        std::exit(code);
    }
}

#endif // LOGGING_HH