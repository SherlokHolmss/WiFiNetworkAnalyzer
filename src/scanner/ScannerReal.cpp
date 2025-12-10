// ScannerReal.cpp
#include "../utils/Types.h"
#include "../scanner/ScannerReal.h"
#include "../utils/Constants.h"
#include "../parser/Parser.h"
#include <iostream>
#include <array>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>

namespace wifi {
    netWorkList realScanner::scanNetworks() {
        netWorkList result;

        std::string command = wifi::constants::netsh_command;
        std::array<char, wifi::constants::buffer_size> buffer{};
        std::string output;

        std::unique_ptr<FILE, decltype(&_pclose)>
                pipe(_popen(command.c_str(), "r"), _pclose);

        if (!pipe) {
            throw std::runtime_error("Не вдалося виконати команду netsh!");
        }

        while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe.get()) != nullptr) {
            output += buffer.data();
        }

        std::stringstream ss(output);
        std::string line;

        wifi::wifiNetwork current{};
        bool inBlock = false;
        wifi::Parser parser;
        netWorkList parsed = parser.parseFromString(output);

        std::sort(parsed.begin(), parsed.end(), [](const wifiNetwork &a, const wifiNetwork &b) {
            return a.signalStrength > b.signalStrength;
        });

        return parsed;
    }
}
