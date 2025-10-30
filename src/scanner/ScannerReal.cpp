//
// Created by USER on 24.10.2025.
//
#include "../utils/Types.h"
#include "../scanner/ScannerReal.h"
#include <iostream>

namespace wifi {
    netWorkList realScanner::scanNetworks() {
        std::cout << "Scanning REAL networks..." << std::endl;
        netWorkList networks = {
            {"Home_WiFi", "AA:BB:CC:DD:EE:FF", -60, 11, 3},
            {"Office_5G", "11:22:33:44:55:66", -40, 36, 4},
            {"Guest_Net", "77:88:99:AA:BB:CC", -75, 6, 2}
        };
        std::cout << "Знайдено - "<< networks.size() <<"Мереж" << std::endl;
        return {};
    }
}
