//
// Created by USER on 25.10.2025.
//

#ifndef WIFINETWORKANALYZER_LOGGER_H
#define WIFINETWORKANALYZER_LOGGER_H
#include <string>

namespace wifi {
    class Logger {
    public:
        void info(const std::string &msg);

        void warning(const std::string &msg);

        void error(const std::string &msg);

    private:
        std::string getCurrentTime();
    };
}

#endif //WIFINETWORKANALYZER_LOGGER_H
