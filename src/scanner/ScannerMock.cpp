//
// Created by USER on 21.10.2025.
//

#include "ScannerMock.h"

#include "../utils/Types.h"

namespace wifi {
    netWorkList ScannerMock::scanNetworks() {
        netWorkList list = {
            {"DUIKT_FREE", "AA:BB:CC:11:22:33", -45, 6, 1},
            {"CampusNet", "DD:EE:FF:44:55:66", -70, 11, 2},
            {"92-4", "DD:EE:FF:57:8:9", -3, 12, 3},
            {"92-3", "DD:FF:EE:45:3:6", -66, 20, 1}
        };
        return list;
    }
}
