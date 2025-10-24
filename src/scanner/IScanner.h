#ifndef WIFINETWORKANALYZER_ISCANNER_H
#define WIFINETWORKANALYZER_ISCANNER_H

#include "../utils/Types.h"

namespace wifi {
    class IScanner {
    public:
        virtual netWorkList scanNetworks() = 0;
        virtual ~IScanner() = default;
    };
}

#endif //WIFINETWORKANALYZER_ISCANNER_H
