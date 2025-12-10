
#pragma once

#include "../utils/Types.h"
#include <string>

namespace wifi {

    class Parser {
    public:
        netWorkList parseFromString(const std::string &output) const;
    };

}
