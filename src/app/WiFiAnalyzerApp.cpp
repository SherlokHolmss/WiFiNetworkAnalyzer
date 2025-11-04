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
                    logger.info("Користувач обрав realScanner");
                    networks = real.scanNetworks();
                    scannerChoiceLoop = false;
                    break;
                }
                case 2: {
                    scannerMock mock;
                    logger.info("Користувач обрав scannerMock");
                    networks = mock.scanNetworks();
                    scannerChoiceLoop = false;
                    break;
                }
                default: {
                    std::cout << "Невірний вибір сканеру!"<< std::endl;
                    logger.warning("Невірний вибір сканеру!");
                    break;
                }
            }
        }
        return networks;
    }


    void WifiAnalyzerApp::renderSelection(const netWorkList &networks) {
        auto analyzed = analyzer->analyze(networks);

        bool renderChoiceLoop = true;
        while (renderChoiceLoop) {
            int renderChoice = renderer->selectRenderMode();
            switch (renderChoice) {
                case 1: {
                    renderer->fullRender(analyzed);
                    analyzer->printSummary(networks);
                    logger.info("Користувач обрав fullRender");
                    renderChoiceLoop = false;
                    break;
                }
                case 2: {
                    renderer->shortRender(analyzed);
                    analyzer->printSummary(networks);
                    logger.info("Користувач обрав shortRender");
                    renderChoiceLoop = false;
                    break;
                }
                default: {
                    logger.warning("Невірний вибір рендеру!");
                    std::cout << "Невірний вибір рендеру!"<< std::endl;
                    break;
                }
            }
        }
    }


    void WifiAnalyzerApp::additionalOptionsSelection(const netWorkList &networks) {
        bool otherOptions = true;

        while (otherOptions) {
            int option = renderer->additionalOptions();
            switch (option) {
                case 1: {
                    std::cout << "Найсильніша мережа: "
                            << analyzer->getStrongestNetwork(networks)
                            << std::endl;
                    logger.info("Знайдено найсильнішу мережу");
                    break;
                }
                case 2: {
                    std::cout << "Найзахищеніша мережа: "
                            << analyzer->getMostSecureNetwork(networks)
                            << std::endl;
                    logger.info("Знайдено найзахищенішу мережу");
                    break;
                }
                case 3: {
                    otherOptions = false;
                    break;
                }
                default: {
                    logger.warning("Невірний вибір!");
                    std::cout << "Невірний вибір"<< std::endl;
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
