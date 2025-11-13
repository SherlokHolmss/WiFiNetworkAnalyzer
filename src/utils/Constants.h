//
// Created by USER on 13.11.2025.
//

#ifndef WIFINETWORKANALYZER_CONSTANTS_H
#define WIFINETWORKANALYZER_CONSTANTS_H

#pragma once
#include <string>

namespace wifi::constants {
    inline const std::string log_file_path = "logs.txt";
    inline const std::string netsh_command = "netsh wlan show networks mode=bssid";
    inline const int buffer_size = 256;
}



#endif //WIFINETWORKANALYZER_CONSTANTS_H