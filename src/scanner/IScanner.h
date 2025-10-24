//
// Created by USER on 24.10.2025.
//

#ifndef WIFINETWORKANALYZER_ISCANNER_H
#define WIFINETWORKANALYZER_ISCANNER_H

#endif //WIFINETWORKANALYZER_ISCANNER_H
#include "../utils/Types.h"

namespace wifi {
    class IScanner {
        public:
        virtual netWorkList scanNetworks() = 0;
    };
}