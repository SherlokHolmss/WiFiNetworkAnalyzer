//
// Created by USER on 24.10.2025.
//

#ifndef WIFINETWORKANALYZER_SCANNERREAL_H
#define WIFINETWORKANALYZER_SCANNERREAL_H

#pragma once

#include "../utils/Types.h"
#include "../scanner/IScanner.h"

namespace wifi {
    class realScanner : public IScanner {
    public:
        netWorkList scanNetworks() override;
    };
}


#endif //WIFINETWORKANALYZER_SCANNERREAL_H
