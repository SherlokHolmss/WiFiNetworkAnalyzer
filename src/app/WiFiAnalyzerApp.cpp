//
// Created by USER on 24.10.2025.
//

#include "WiFiAnalyzerApp.h"

#include <iostream>
#include <ostream>

#include "../analyzer/Analyzer.h"
#include "../renderer/ConsoleRenderer.h"
#include "../scanner/ScannerMock.h"
#include "../scanner/ScannerReal.h"
#include "../utils/Logger.h"

namespace wifi {
    WifiAnalyzerApp::WifiAnalyzerApp(IScanner *scanner, Analyzer *analyzer, ConsoleRenderer *renderer)
        : scanner(scanner), analyzer(analyzer), renderer(renderer) {
    }

    void WifiAnalyzerApp::run() {
        Logger logger;
        logger.info("Програма Запущена");
        WifiAnalyzerApp::mainMenu();
    }

    netWorkList WifiAnalyzerApp::scannerSelection() {
        netWorkList networks;

        bool scannerChoiceLoop = true;
        while (scannerChoiceLoop) {
            int scannerChoice = renderer->selectScannerMode();
            switch (scannerChoice) {
                case 1: {
                    realScanner real;
                    networks = real.scanNetworks();
                    scannerChoiceLoop = false;
                    break;
                }
                case 2: {
                    scannerMock mock;
                    networks = mock.scanNetworks();
                    scannerChoiceLoop = false;
                    break;
                }
                default: {
                    logger.warning("Невірний вибір сканеру!");
                    break;
                }
            }
        }
        return networks;
    }


    void WifiAnalyzerApp::renderSelection(const netWorkList& networks) {
        auto analyzed = analyzer->analyze(networks);

        bool renderChoiceLoop = true;
        while (renderChoiceLoop) {
            int renderChoice = renderer->selectRenderMode();
            switch (renderChoice) {
                case 1: {
                    renderer->fullRender(analyzed);
                    analyzer->printSummary(networks);
                    renderChoiceLoop = false;
                    break;
                }
                case 2: {
                    renderer->shortRender(analyzed);
                    analyzer->printSummary(networks);
                    renderChoiceLoop = false;
                    break;
                }
                default: {
                    logger.warning("Невірний вибір рендеру!");
                    break;
                }
            }
        }
    }


    void WifiAnalyzerApp::additionalOptionsSelection(const netWorkList& networks) {
        bool otherOptions = true;

        while (otherOptions) {
            int option = renderer->additionalOptions();
            switch (option) {
                case 1: {
                    std::cout << "Найсильніша мережа: "
                              << analyzer->getStrongestNetwork(networks)
                              << std::endl;
                    break;
                }
                case 2: {
                    std::cout << "Найзахищеніша мережа: "
                              << analyzer->getMostSecureNetwork(networks)
                              << std::endl;
                    break;
                }
                case 3: {
                    otherOptions = false;
                    break;
                }
                default: {
                    logger.warning("Невірний вибір!");
                    break;
                }
            }
        }
    }


    void WifiAnalyzerApp::mainMenu() {
        bool eventLoop = true;

        while (eventLoop) {
            int mainChoice = renderer->mainMenu();

            switch (mainChoice) {
                case 1: {
                    netWorkList networks = scannerSelection();
                    renderSelection(networks);
                    additionalOptionsSelection(networks);
                    break;
                }
                case 2: {
                    logger.info("Програма завершена користувачем.");
                    eventLoop = false;
                    break;
                }
                default: {
                    logger.warning("Невірний вибір!");
                    break;
                }
            }
        }
    }

}
