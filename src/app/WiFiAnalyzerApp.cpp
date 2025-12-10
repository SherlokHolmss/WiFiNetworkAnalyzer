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
#include "../utils/MenuOptions.h"

namespace wifi {
    WifiAnalyzerApp::WifiAnalyzerApp(IScanner *scanner, Analyzer *analyzer, ConsoleRenderer *renderer)
        : scanner(scanner),
          analyzer(analyzer),
          renderer(renderer)
    {
    }

    void WifiAnalyzerApp::run() {
        Logger::instance().info("Сканування запущено");

        WifiAnalyzerApp::mainMenu();
    }

    netWorkList WifiAnalyzerApp::scannerSelection() {
        netWorkList networks;

        bool scannerChoiceLoop = true;
        while (scannerChoiceLoop) {
            int scannerChoiceInt = renderer->selectScannerMode(std::cout);
            auto scannerChoice = static_cast<ScannerMode>(scannerChoiceInt);

            switch (scannerChoice) {
                case wifi::ScannerMode::Real: {
                    realScanner real;
                    Logger::instance().info("Користувач обрав realScanner");
                    networks = real.scanNetworks();
                    scannerChoiceLoop = false;
                    break;
                }
                case wifi::ScannerMode::Mock: {
                    scannerMock mock;
                    Logger::instance().info("Користувач обрав scannerMock");
                    networks = mock.scanNetworks();
                    scannerChoiceLoop = false;
                    break;
                }
                default: {
                    std::cout << "Невірний вибір сканеру!" << std::endl;
                    Logger::instance().warning("Невірний вибір сканеру!");
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
            int renderChoiceInt = renderer->selectRenderMode(std::cout);
            auto renderChoice = static_cast<wifi::RenderMode>(renderChoiceInt);


            switch (renderChoice) {
                case wifi::RenderMode::Full: {
                    renderer->fullRender(analyzed, std::cout);
                    analyzer->printSummary(networks);
                    Logger::instance().info("Користувач обрав fullRender");
                    renderChoiceLoop = false;
                    break;
                }
                case wifi::RenderMode::Short: {
                    renderer->shortRender(analyzed, std::cout);
                    analyzer->printSummary(networks);
                    Logger::instance().info("Користувач обрав shortRender");
                    renderChoiceLoop = false;
                    break;
                }
                default: {
                    Logger::instance().warning("Невірний вибір рендеру!");
                    std::cout << "Невірний вибір рендеру!" << std::endl;
                    break;
                }
            }
        }
    }


    void WifiAnalyzerApp::additionalOptionsSelection(const netWorkList &networks) {
        bool otherOptions = true;

        while (otherOptions) {
            int optionInt = renderer->additionalOptions(std::cout);
            auto option = static_cast<wifi::AdditionalOptions>(optionInt);


            switch (option) {
                case wifi::AdditionalOptions::Strongest: {
                    std::cout << "Найсильніша мережа: "
                            << analyzer->getStrongestNetwork(networks)
                            << std::endl;
                    Logger::instance().info("Знайдено найсильнішу мережу");
                    break;
                }
                case wifi::AdditionalOptions::Securest: {
                    std::cout << "Найзахищеніша мережа: "
                            << analyzer->getMostSecureNetwork(networks)
                            << std::endl;
                    Logger::instance().info("Знайдено найзахищенішу мережу");
                    break;
                }
                case wifi::AdditionalOptions::Back: {
                    otherOptions = false;
                    break;
                }
                default: {
                    Logger::instance().warning("Невірний вибір!");
                    std::cout << "Невірний вибір" << std::endl;
                    break;
                }
            }
        }
    }

    void WifiAnalyzerApp::processScanningFlow() {
        netWorkList networks = scannerSelection();
        renderSelection(networks);
        additionalOptionsSelection(networks);
    }


    void WifiAnalyzerApp::mainMenu() {
        bool eventLoop = true;


        while (eventLoop) {
            int mainChoiceInt = renderer->mainMenu(std::cout);
            auto mainChoice = static_cast<wifi::MainMenuOption>(mainChoiceInt);

            switch (mainChoice) {
                case wifi::MainMenuOption::ScanNetworks: {
                    processScanningFlow();
                    break;
                }
                case wifi::MainMenuOption::Exit: {
                    Logger::instance().info("Програма завершена користувачем.");
                    eventLoop = false;
                    break;
                }
                default: {
                    Logger::instance().warning("Невірний вибір!");
                    break;
                }
            }
        }
    }
}
