#include "Parser.h"
#include <sstream>
#include <algorithm>
#include <cctype>
#include <string>

namespace wifi {
    static inline std::string trimLeftRight(std::string s) {
        s.erase(s.begin(),
                std::find_if(s.begin(), s.end(),
                             [](unsigned char ch) { return !std::isspace(ch); }));
        s.erase(std::find_if(s.rbegin(), s.rend(),
                             [](unsigned char ch) { return !std::isspace(ch); }).base(),
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
        std::string a = toLowerCopy(trimLeftRight(authRaw));
        if (a.find("wpa3") != std::string::npos) return 4;
        if (a.find("wpa2") != std::string::npos) return 3;
        if (a.find("wpa") != std::string::npos) return 2;
        if (a.find("wep") != std::string::npos) return 1;
        return 0; // open/unknown
    }

    netWorkList Parser::parseFromString(const std::string &output) const {
        netWorkList result;
        std::stringstream ss(output);
        std::string line;

        wifiNetwork current{};
        bool inBlock = false;

        while (std::getline(ss, line)) {
            line = trimLeftRight(line);
            if (line.empty()) continue;

            // SSID
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

            // BSSID
            if (line.rfind("BSSID", 0) == 0) {
                auto pos = line.find(':');
                if (pos != std::string::npos) {
                    current.bssid = trimLeftRight(line.substr(pos + 1));
                }
                continue;
            }

            // Signal
            if (toLowerCopy(line).rfind("signal", 0) == 0) {
                auto pos = line.find(':');
                if (pos != std::string::npos) {
                    std::string val = trimLeftRight(line.substr(pos + 1));
                    val.erase(std::remove(val.begin(), val.end(), '%'), val.end());
                    try { current.signalStrength = std::stoi(val); } catch (...) { current.signalStrength = 0; }
                }
                continue;
            }

            // Channel
            if (toLowerCopy(line).rfind("channel", 0) == 0) {
                auto pos = line.find(':');
                if (pos != std::string::npos) {
                    std::string val = trimLeftRight(line.substr(pos + 1));
                    try { current.channel = std::stoi(val); } catch (...) { current.channel = 0; }
                }
                continue;
            }

            //  WPA/WPA2/WPA3
            if (toLowerCopy(line).rfind("authentication", 0) == 0) {
                auto pos = line.find(':');
                if (pos != std::string::npos) {
                    std::string val = trimLeftRight(line.substr(pos + 1));
                    current.encryption = mapEncryption(val);
                }
                continue;
            }

            // Encryption
            if (toLowerCopy(line).rfind("encryption", 0) == 0) {
                continue;
            }
        }

        // ПУШ
        if (inBlock && !current.ssid.empty()) {
            result.push_back(current);
        }

        // SSID
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
} // namespace wifi
