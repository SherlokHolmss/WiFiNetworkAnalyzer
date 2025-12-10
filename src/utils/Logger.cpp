#include "Logger.h"
#include "Constants.h"

#include <iostream>
#include <sstream>
#include <chrono>
#include <ctime>
#include <iomanip>

namespace wifi {
    static std::string getCurrentTime() {
        auto now = std::chrono::system_clock::now();
        std::time_t t = std::chrono::system_clock::to_time_t(now);
        std::tm localTime{};

#ifdef _WIN32
        localtime_s(&localTime, &t);
#else
        localtime_r(&t, &localTime);
#endif

        std::ostringstream oss;
        oss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }

    Logger &Logger::instance() {
        static Logger instance;
        return instance;
    }

    Logger::Logger() : outStream_(&std::cout) {
        file_.open(wifi::constants::log_file_path, std::ios::app);

        if (!file_.is_open()) {
            std::cerr << "Не вдалося відкрити файл логів!" << std::endl;
        }
    }

    Logger::~Logger() {
        if (file_.is_open()) file_.close();
    }

    void Logger::setOutputStream(std::ostream &out) {
        std::lock_guard<std::mutex> g(mtx_);
        outStream_ = &out;
    }

    void Logger::log(const std::string &level, const std::string &msg) {
        std::lock_guard<std::mutex> g(mtx_);

        std::string line = "[" + getCurrentTime() + "] [" + level + "] " + msg;

        if (outStream_) {
            (*outStream_) << line << std::endl;
        }

        if (file_.is_open()) {
            file_ << line << std::endl;
        }
    }

    void Logger::info(const std::string &msg) {
        log("INFO", msg);
    }

    void Logger::warning(const std::string &msg) {
        log("WARNING", msg);
    }

    void Logger::error(const std::string &msg) {
        log("ERROR", msg);
    }
} // namespace wifi
