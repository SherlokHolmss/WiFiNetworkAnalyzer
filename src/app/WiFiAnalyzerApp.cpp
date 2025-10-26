//
// Created by USER on 24.10.2025.
//

#include "WiFiAnalyzerApp.h"

#include "../analyzer/Analyzer.h"
#include "../renderer/ConsoleRenderer.h"
#include "../scanner/ScannerMock.h"
#include "../utils/Logger.h"
namespace wifi {
    WifiAnalyzerApp::WifiAnalyzerApp(IScanner *scanner, Analyzer *analyzer, ConsoleRenderer *renderer)
        : scanner(scanner), analyzer(analyzer), renderer(renderer) {
    }

    void WifiAnalyzerApp::run() {
        auto networks = scanner->scanNetworks();
        auto analyzed = analyzer->analyze(networks);
        Logger logger;
        logger.info("Програма Запущена");
        renderer->mainMenu(analyzed);
    }
}
