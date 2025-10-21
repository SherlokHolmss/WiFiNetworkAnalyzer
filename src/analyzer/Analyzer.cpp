//
// Created by USER on 11.10.2025.
//
#include  <iostream>
#include "Analyzer.h"
#include <algorithm>

namespace wifi {
    netWorkList Analyzer::analyze(const netWorkList &networks) {
        netWorkList analyzed = networks;
        int strangest = analyzed[0].signalStrength;
        std::string strangestSSID = analyzed[0].ssid;

        for (const auto &net: analyzed) {
            if (net.signalStrength > strangest) {
                strangest = net.signalStrength;
                strangestSSID = net.ssid;
            }
        }
        std::cout << strangest << '-' << strangestSSID << std::endl;
        return analyzed;
    }
}
