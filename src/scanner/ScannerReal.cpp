//
// Created by USER on 24.10.2025.
//
#include "../utils/Types.h"
#include "../scanner/ScannerReal.h"
#include <iostream>
#include <array>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>

#include "../utils/Constants.h"

namespace wifi {
    netWorkList realScanner::scanNetworks() {
        netWorkList result;
        std::string command = wifi::constants::netsh_command;
        std::array<char, wifi::constants::buffer_size> buffer;
        std::string output;

        std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(command.c_str(), "r"), _pclose);
        if (!pipe) throw std::runtime_error("Не вдалося виконати команду netsh!");

        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
            output += buffer.data();
        }
        std::stringstream ss(output);
        std::string line;

        netWorkList current;
        bool inBlock = false;

        while (std::getline(ss, line)) {
            // Прибираємо пробіли з початку
            while (!line.empty() && line[0] == ' ') line.erase(0, 1);

            // Знайшли новий SSID
            if (line.starts_with("SSID ")) {
                if (inBlock && !current.ssid.empty()) {
                    result.push_back(current);
                }

                current = netWorkList{};
                inBlock = true;

                auto pos = line.find(":");
                if (pos != std::string::npos) {
                    current.ssid = line.substr(pos + 1);
                    // видаляємо пробіли
                    while (!current.ssid.empty() && current.ssid[0] == ' ')
                        current.ssid.erase(0, 1);
                }
                continue;
            }

            // Signal
            if (line.starts_with("Signal")) {
                auto pos = line.find(":");
                if (pos != std::string::npos) {
                    std::string val = line.substr(pos + 1);
                    val.erase(remove(val.begin(), val.end(), '%'), val.end());
                    current.signal = std::stoi(val);
                }
                continue;
            }

            // Authentication
            if (line.starts_with("Authentication")) {
                auto pos = line.find(":");
                if (pos != std::string::npos) {
                    std::string val = line.substr(pos + 1);
                    while (!val.empty() && val[0] == ' ')
                        val.erase(0, 1);
                    current.encryption = mapEncryption(val);
                }
                continue;
            }
        }

        // додаємо останню мережу
        if (inBlock && !current.ssid.empty()) {
            result.push_back(current);
        }

        std::cout << output;
        return result;
    }
}
