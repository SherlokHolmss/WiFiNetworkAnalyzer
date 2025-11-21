// ScannerReal.cpp
#include "../utils/Types.h"
#include "../scanner/ScannerReal.h"
#include "../utils/Constants.h"

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
    static inline std::string trimLeftRight(std::string s) {
        s.erase(s.begin(),
                std::find_if(s.begin(), s.end(),
                             [](unsigned char ch) { return !std::isspace(ch); }));

        s.erase(std::find_if(s.rbegin(), s.rend(),
                             [](unsigned char ch) { return !std::isspace(ch); })
                .base(),
                s.end());

        return s;
    }

    static inline std::string toLowerCopy(const std::string &s) {
        std::string r = s;
        std::transform(r.begin(), r.end(), r.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        return r;
    }

    static int mapEncryption(const std::string &authRaw) {
        std::string a = toLowerCopy(authRaw);
        a = trimLeftRight(a);

        if (a.find("wpa3") != std::string::npos) return 4;
        if (a.find("wpa2") != std::string::npos) return 3;

        if (a.find("wpa") != std::string::npos) return 2;

        if (a.find("wep") != std::string::npos) return 1;

        return 0;
    }

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

        while (std::getline(ss, line)) {
            line = trimLeftRight(line);
            if (line.empty()) continue;

            if (line.rfind("SSID ", 0) == 0) {
                if (inBlock && !current.ssid.empty()) {
                    result.push_back(current);
                    current = wifiNetwork{};
                }

                inBlock = true;

                auto pos = line.find(':');
                if (pos != std::string::npos) {
                    current.ssid = trimLeftRight(line.substr(pos + 1));
                } else {
                    current.ssid.clear();
                }

                continue;
            }

            if (line.rfind("BSSID", 0) == 0) {
                auto pos = line.find(':');
                if (pos != std::string::npos) {
                    current.bssid = trimLeftRight(line.substr(pos + 1));
                }

                continue;
            }

            if (toLowerCopy(line).rfind("signal", 0) == 0) {
                auto pos = line.find(':');
                if (pos != std::string::npos) {
                    std::string val = trimLeftRight(line.substr(pos + 1));
                    val.erase(std::remove(val.begin(), val.end(), '%'), val.end());

                    try {
                        current.signalStrength = std::stoi(val);
                    } catch (...) {
                        current.signalStrength = 0;
                    }
                }

                continue;
            }

            if (toLowerCopy(line).rfind("channel", 0) == 0) {
                auto pos = line.find(':');
                if (pos != std::string::npos) {
                    std::string val = trimLeftRight(line.substr(pos + 1));

                    try {
                        current.channel = std::stoi(val);
                    } catch (...) {
                        current.channel = 0;
                    }
                }

                continue;
            }

            std::string lower = toLowerCopy(line);

            if (lower.rfind("authentication", 0) == 0) {
                auto pos = line.find(':');
                if (pos != std::string::npos) {
                    std::string val = trimLeftRight(line.substr(pos + 1));
                    current.encryption = mapEncryption(val);
                }

                continue;
            }

            if (lower.rfind("encryption", 0) == 0) {
            }
        }

        if (inBlock && !current.ssid.empty()) {
            result.push_back(current);
        }

        netWorkList filtered;

        for (const auto &n: result) {
            if (n.ssid.empty()) continue;

            bool duplicate = false;

            for (const auto &f: filtered) {
                if (f.ssid == n.ssid) {
                    duplicate = true;
                    break;
                }
            }

            if (!duplicate) filtered.push_back(n);
        }

        return filtered;
    }
}
