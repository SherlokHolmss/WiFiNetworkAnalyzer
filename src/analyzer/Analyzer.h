//
// Created by USER on 11.10.2025.
//

#ifndef WIFINETWORKANALYZER_ANALYZER_H
#define WIFINETWORKANALYZER_ANALYZER_H
#include "../utils/Types.h"

#endif //WIFINETWORKANALYZER_ANALYZER_H

namespace wifi {
    class Analyzer {
    public:
        netWorkList analyze(const wifi::netWorkList &networks);
    };
}
