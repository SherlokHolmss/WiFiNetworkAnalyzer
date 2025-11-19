// ScannerReal.cpp
// Created by USER on ...
#include "../utils/Types.h"
#include "../scanner/ScannerReal.h"
#include <iostream>
#include <array>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>

#include "../utils/Constants.h"

namespace wifi {
    static inline std::string trim_left_right(std::string s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
            return !std::isspace(ch);
        }));
        s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
            return !std::isspace(ch);
        }).base(), s.end());
        return s;
    }

    static inline std::string to_lower_copy(const std::string &s) {
        std::string r = s;
        std::transform(r.begin(), r.end(), r.begin(), [](unsigned char c) { return std::tolower(c); });
        return r;
    }

    static int map_encryption(const std::string &auth) {
        std::string a = to_lower_copy(auth);
        if (a.find("WPA3") != std::string::npos) return 4;
        if (a.find("WPA2") != std::string::npos) return 3;
        if (a.find("WPA") != std::string::npos) return 2;
        if (a.find("WEP") != std::string::npos) return 1;
        return 0;
    }

    netWorkList realScanner::scanNetworks() {
        netWorkList result;
        std::string command = wifi::constants::netsh_command;
        std::array<char, wifi::constants::buffer_size> buffer;
        std::string output;

        std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(command.c_str(), "r"), _pclose);
        if (!pipe) {
            throw std::runtime_error("Не вдалося виконати команду netsh!");
        }

        while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe.get()) != nullptr) {
            output += buffer.data();
        }


        std::stringstream ss(output);
        std::string line;

        wifi::wifiNetwork current{};
        bool in_block = false;

        while (std::getline(ss, line)) {
            line = trim_left_right(line);
            if (line.empty()) continue;

            if (line.rfind("SSID ", 0) == 0) {
                if (in_block && !current.ssid.empty()) {
                    result.push_back(current);
                    current = wifiNetwork{};
                }
                in_block = true;
                auto pos = line.find(':');
                if (pos != std::string::npos) {
                    std::string ssid_val = line.substr(pos + 1);
                    current.ssid = trim_left_right(ssid_val);
                } else {
                    current.ssid.clear();
                }
                continue;
            }


            if (line.rfind("BSSID", 0) == 0) {
                auto pos = line.find(':');
                if (pos != std::string::npos) {
                    std::string bssid_val = line.substr(pos + 1);
                    current.bssid = trim_left_right(bssid_val);
                }
                continue;
            }


            if (to_lower_copy(line).rfind("signal", 0) == 0) {
                auto pos = line.find(':');
                if (pos != std::string::npos) {
                    std::string val = trim_left_right(line.substr(pos + 1));
                    val.erase(std::remove(val.begin(), val.end(), '%'), val.end());
                    try {
                        current.signalStrength = std::stoi(val);
                    } catch (...) {
                        current.signalStrength = 0;
                    }
                }
                continue;
            }

            if (to_lower_copy(line).rfind("channel", 0) == 0) {
                auto pos = line.find(':');
                if (pos != std::string::npos) {
                    std::string val = trim_left_right(line.substr(pos + 1));
                    try {
                        current.channel = std::stoi(val);
                    } catch (...) {
                        current.channel = 0;
                    }
                }
                continue;
            }
            if (to_lower_copy(line).rfind("authentication", 0) == 0 ||
                to_lower_copy(line).rfind("encryption", 0) == 0) {
                auto pos = line.find(':');
                if (pos != std::string::npos) {
                    std::string val = trim_left_right(line.substr(pos + 1));
                    current.encryption = map_encryption(val);
                }
                continue;
            }
        }

        if (in_block && !current.ssid.empty()) {
            result.push_back(current);
        }

        netWorkList filtered;
        for (const auto &n: result) {
            if (n.ssid.empty()) continue;
            bool dup = false;
            for (const auto &f: filtered) {
                if (f.ssid == n.ssid) {
                    dup = true;
                    break;
                }
            }
            if (!dup) filtered.push_back(n);
        }


        return filtered;
    }
}
