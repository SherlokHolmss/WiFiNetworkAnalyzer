#pragma once
#include <string>
#include <vector>

namespace wifi {
    struct wifiNetwork {
        std::string ssid;
        std::string bssid;
        int signalStrength;
        int channel;
        int encryption;
    };

    struct resultAnalyze {
        std::string name;
        std::string macAddress;
        std::string signalStrength;
        std::string channel;
        std::string encryption;
    };

    using resultAnalyzeList = std::vector<resultAnalyze>;
    using netWorkList = std::vector<wifiNetwork>;
}
