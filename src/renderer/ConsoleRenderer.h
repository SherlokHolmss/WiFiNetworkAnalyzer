//
// Created by USER on 11.10.2025.
//

#ifndef WIFINETWORKANALYZER_CONSOLERENDERER_H
#define WIFINETWORKANALYZER_CONSOLERENDERER_H

#endif //WIFINETWORKANALYZER_CONSOLERENDERER_H
#pragma once
#include "../utils/Types.h"


namespace wifi {
    class ConsoleRenderer {
    public:
        int selectScannerMode(const resultAnalyzeList& networks);
        int selectRenderMode(const resultAnalyzeList& networks);
        void fullRender(const resultAnalyzeList& networks);
        void shortRender(const resultAnalyzeList& networks);
    };
}
