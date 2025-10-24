//
// Created by USER on 24.10.2025.
//

#ifndef WIFINETWORKANALYZER_WIFIANALYZERAPP_H
#define WIFINETWORKANALYZER_WIFIANALYZERAPP_H


#pragma once
#include "../analyzer/Analyzer.h"
#include "../scanner/IScanner.h"
#include "../renderer/ConsoleRenderer.h"

namespace wifi {
    class WifiAnalyzerApp {
    public:
        void run();

        WifiAnalyzerApp(IScanner *scanner, Analyzer *analyzer, ConsoleRenderer *console);

    private:
        IScanner *scanner;
        Analyzer *analyzer;
        ConsoleRenderer *renderer;
    };
}
#endif //WIFINETWORKANALYZER_WIFIANALYZERAPP_H
