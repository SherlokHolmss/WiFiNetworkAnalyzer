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

    using netWorkList = std::vector<wifiNetwork>;
}
