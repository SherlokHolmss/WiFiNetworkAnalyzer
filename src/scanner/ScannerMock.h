//
// Created by USER on 21.10.2025.
//

#ifndef WIFINETWORKANALYZER_SCANNERMOCK_H
#define WIFINETWORKANALYZER_SCANNERMOCK_H
#pragma once

#include "IScanner.h"
#include "../utils/Types.h"


#endif //WIFINETWORKANALYZER_SCANNERMOCK_H


namespace wifi {
    class ScannerMock : public IScanner {
    public:
        netWorkList scanNetworks();
    };
}
