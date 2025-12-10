//
// Created by USER on 24.10.2025.
//

#ifndef WIFINETWORKANALYZER_WIFIANALYZERAPP_H
#define WIFINETWORKANALYZER_WIFIANALYZERAPP_H


#pragma once
#include "../analyzer/Analyzer.h"
#include "../scanner/IScanner.h"
#include "../renderer/ConsoleRenderer.h"
#include "../utils/Logger.h"


namespace wifi {
    class WifiAnalyzerApp {
    public:
        void run();

        WifiAnalyzerApp(IScanner *scanner, Analyzer *analyzer, ConsoleRenderer *console);

    private:
        IScanner *scanner;
        Analyzer *analyzer;
        ConsoleRenderer *renderer;

        void processScanningFlow();

        netWorkList scannerSelection();

        void renderSelection(const netWorkList &networks);

        void additionalOptionsSelection(const netWorkList &networks);

        void mainMenu();
    };
}
#endif //WIFINETWORKANALYZER_WIFIANALYZERAPP_H
