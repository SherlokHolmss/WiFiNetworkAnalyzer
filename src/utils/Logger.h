//
// Created by USER on 25.10.2025.
//

#ifndef WIFINETWORKANALYZER_LOGGER_H
#define WIFINETWORKANALYZER_LOGGER_H
#include <string>
#include <fstream>
#include <mutex>

namespace wifi {
    class Logger {
    public:
        static Logger &instance();

        void info(const std::string &msg);

        void warning(const std::string &msg);

        void error(const std::string &msg);

        void setOutputStream(std::ostream &out);

    private:
        Logger();

        ~Logger();

        void log(const std::string &level, const std::string &msg);

        std::ostream *outStream_;
        std::ofstream file_;
        std::mutex mtx_;
    };
}

#endif //WIFINETWORKANALYZER_LOGGER_H
