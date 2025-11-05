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
namespace wifi {
    netWorkList realScanner::scanNetworks() {
        netWorkList list = {
            {"netis_42E5BC", "AA:BB:CC:11:22:33", -45, 6, 1},
            {"Lisoka", "DD:EE:FF:44:55:66", -70, 11, 2},
            {"Room 2.4G", "DD:EE:FF:57:8:9", -3, 5, 3},
            {"Room 5G", "DD:FF:EE:45:3:6", -66, 20, 1}
        };
        return list;
    }
}
