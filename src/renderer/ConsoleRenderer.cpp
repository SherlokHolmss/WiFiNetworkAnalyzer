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

    int ConsoleRenderer::safeInput(int min, int max) {
        int value;
        while (true) {
            if (std::cin >> value && value >= min && value <= max) {
                return value;
            }
            else {
                std::cin.clear();
                std::cin.ignore(100, '\n');
                std::cout << "Невірне введеня!" << std::endl;
            }
        }

    }


    int ConsoleRenderer::mainMenu() {
        std::cout << "Головне меню" << std::endl;
        std::cout << "1.Почати роботу" << std::endl;
        std::cout << "2.Вийти" << std::endl;
        int mode = safeInput(1, 2);
        return mode;
    }

    int ConsoleRenderer::additionalOptions() {
        std::cout << "Додаткові опції:" << std::endl;
        std::cout << "<--------------------------->\n";
        std::cout << "1.Знайти найсильнішу мережу" << std::endl;
        std::cout << "2.Знайти найзахищенішу мережу" << std::endl;
        std::cout << "3.Повернутись у головне меню" << std::endl;
        std::cout << "4.Вийти" << std::endl;
        std::cout << "<--------------------------->\n";
        int mode = safeInput(1, 4);
        return mode;
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

    int ConsoleRenderer::selectRenderMode() {
        std::cout << "Оберіть режим:" << std::endl;
        std::cout << "1.Повне сканування" << std::endl;
        std::cout << "2.Коротке сканування" << std::endl;
        int mode = safeInput(1, 2);
        return mode;
    }

    int ConsoleRenderer::selectScannerMode() {
        std::cout << "Оберіть режим сканеру" << std::endl;
        std::cout << "1.RealScanner" << std::endl;
        std::cout << "2.MockScanner" << std::endl;
        int mode = safeInput(1, 2);
        return mode;
    }
}
