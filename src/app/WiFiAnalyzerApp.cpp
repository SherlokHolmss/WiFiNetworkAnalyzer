//
// Created by USER on 24.10.2025.
//

#include "WiFiAnalyzerApp.h"

#include "../analyzer/Analyzer.h"
#include "../renderer/ConsoleRenderer.h"
#include "../scanner/ScannerMock.h"

namespace wifi {
    void WifiAnalyzerApp::run() {
        wifi::ScannerMock scanner;
        wifi::Analyzer analyzer;
        wifi::ConsoleRenderer renderer;
        auto networks = scanner.scanNetworks();
        auto analyzed = analyzer.analyze(networks);
        renderer.selectRenderMode(analyzed);
    }

}
