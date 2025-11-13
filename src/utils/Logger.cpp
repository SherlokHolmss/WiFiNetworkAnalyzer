//
// Created by USER on 25.10.2025.
//
#include "Logger.h"
#include <fstream>
#include <iostream>
#include <ctime>
#include <iomanip>

#include "Constants.h"

namespace wifi {
    std::string getCurrentTime() {
        std::time_t now = std::time(nullptr);
        std::tm localTime{};
#ifdef _WIN32
        localtime_s(&localTime, &now);
#else
        localtime_r(&now, &localTime);
#endif
        std::ostringstream oss;
        oss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }

    void writeToFile(const std::string &level, const std::string &msg) {
        std::ofstream logFile(wifi::constants::log_file_path, std::ios::app);
        if (logFile.is_open()) {
            logFile << "[" << getCurrentTime() << "] "
                    << "[" << level << "] " << msg << std::endl;
        }
    }


    void Logger::info(const std::string &msg) {
        std::string logLine = "[INFO] " + msg;
        std::cout << logLine << std::endl;
        writeToFile("info", logLine);
    }

    void Logger::warning(const std::string &msg) {
        std::string logLine = "[WARNING] " + msg;
        std::cout << logLine << std::endl;
        writeToFile("WARNING", logLine);
    }

    void Logger::error(const std::string &msg) {
        std::string logLine = "[ERROR] " + msg;
        std::cout << logLine << std::endl;
        writeToFile("ERROR", logLine);
    }
}
