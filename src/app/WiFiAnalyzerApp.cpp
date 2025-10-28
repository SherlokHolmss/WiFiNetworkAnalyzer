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

        bool eventLoop = true;

        while (eventLoop) {
            int mainChoice = renderer->mainMenu();

            switch (mainChoice) {
                case 1: {
                    int scannerChoise = renderer->selectScannerMode();
                    netWorkList networks;

                    if (scannerChoise == 1) {
                        realScanner real;
                        networks = real.scanNetworks();
                    } else {
                        scannerMock mock;
                        networks = mock.scanNetworks();
                    }

                    auto analyzed = analyzer->analyze(networks);

                    int renderChoise = renderer->selectRenderMode();
                    if (renderChoise == 1) {
                        renderer->fullRender(analyzed);
                    } else {
                        renderer->shortRender(analyzed);
                    }

                    bool otherOptions = true;
                    while (otherOptions) {
                        int option = renderer->additionalOptions();

                        switch (option) {
                            case 1: {
                                std::cout << "Найсильніша мережа:";
                                std::cout << analyzer->getStrongestNetwork(networks);
                                std::cout << std::endl;
                                break;
                            }
                            case 2: {
                                std::cout << "Найзахищеніша мережа:";
                                std::cout << analyzer->getStrongestNetwork(networks);
                                std::cout << std::endl;
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
                    break;
                }
                case 2: {
                    logger.info("Програма завершена користувачем");
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
