//
// Created by USER on 13.11.2025.
//

#ifndef WIFINETWORKANALYZER_MENUOPTIONS_H
#define WIFINETWORKANALYZER_MENUOPTIONS_H
#pragma once

namespace wifi {

    enum class MainMenuOption {
        ScanNetworks = 1,
        Exit = 2
    };


    enum class ScannerMode  {
        Real = 1,
        Mock = 2
    };

    enum class RenderMode {
        Full = 1,
        Short = 2
    };

    enum class AdditionalOptions {
        Strongest = 1,
        Securest = 2,
        Back = 3,
        Exit = 4
    };
}




#endif //WIFINETWORKANALYZER_MENUOPTIONS_H