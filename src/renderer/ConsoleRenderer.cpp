//
// Created by USER on 11.10.2025.
//
#include <iostream>
#include "ConsoleRenderer.h"
#include "../analyzer/Analyzer.h"
#include "../scanner/ScannerMock.h"
#include "../scanner/ScannerReal.h"
#include "../utils/Logger.h"

namespace wifi {
    Logger logger;
    void ConsoleRenderer::mainMenu(const resultAnalyzeList &networks) {
        int mode = 0;
        std::cout << "Головне меню" << std::endl;
        std::cout << "1.Почати роботу" << std::endl;
        std::cout << "2.Вийти" << std::endl;
        std::cin >> mode;

        switch (mode) {
            case 1: {
                selectScannerMode(networks);
                return;
            }
            case 2: {
                std::cout << "Програма закінчила свою роботу!";
                exit(0);
            }
            default: {
                std::cout << "Виберіть правильну опцію!";
                break;
            }
        }
    }

    void ConsoleRenderer::shortRender(const resultAnalyzeList &results) {
        std::cout << "SHORT MOCK DATA" << std::endl;
        for (const auto &res: results) {
            std::cout << "<--------------------------->\n";
            std::cout << "SSID: " << res.name << "\n";
            std::cout << "Сигнал: " << res.signalStrength << "\n";
            std::cout << "Безпека: " << res.encryption << "\n";
            std::cout << "<--------------------------->\n";
        }
    }

    void ConsoleRenderer::fullRender(const resultAnalyzeList &results) {
        std::cout << "FULL MOCK DATA" << std::endl;
        for (const auto &res: results) {
            std::cout << "<--------------------------->\n";
            std::cout << "SSID: " << res.name << "\n";
            std::cout << "MAC: " << res.macAddress << "\n";
            std::cout << "Сигнал: " << res.signalStrength << "\n";
            std::cout << "Діапазон: " << res.channel << "\n";
            std::cout << "Безпека: " << res.encryption << "\n";
            std::cout << "<--------------------------->\n";
        }

    }

    int ConsoleRenderer::selectRenderMode(const resultAnalyzeList &results) {
        int mode = 0;

        std::cout << "Оберіть режим:" << std::endl;
        std::cout << "1.Повне сканування" << std::endl;
        std::cout << "2.Коротке сканування" << std::endl;
        std::cin >> mode;
        switch (mode) {
            case 1:
                fullRender(results);
                mainMenu(results);
                return 1;
            case 2:
                shortRender(results);
                mainMenu(results);
                return 2;
            default: {
                logger.warning("Оберіть правельний режим!");
                selectRenderMode(results);
            }
        }
    }

    int ConsoleRenderer::selectScannerMode(const resultAnalyzeList &results) {
        int mode = 0;

        std::cout << "Оберіть режим сканеру" << std::endl;
        std::cout << "1.RealScanner" << std::endl;
        std::cout << "2.MockScanner" << std::endl;
        std::cin >> mode;
        switch (mode) {
            case 1: {
                realScanner real;
                auto networks = real.scanNetworks();
                selectRenderMode(results);
                return 1;
            }
            case 2: {
                scannerMock mock;
                auto networks = mock.scanNetworks();
                selectRenderMode(results);
                return 2;
            }
            default: {
                logger.warning("Оберіть правельний режим!");
                selectScannerMode(results);
            }
        }
    }
}
