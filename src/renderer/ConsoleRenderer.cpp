//
// Created by USER on 11.10.2025.
//
#include <iostream>
#include "ConsoleRenderer.h"
#include "../analyzer/Analyzer.h"
#include "../utils/Logger.h"

namespace wifi {

    void ConsoleRenderer::write(std::ostream& out, const std::string& text) {
        out << text;
    }

    void ConsoleRenderer::writeLine(std::ostream& out, const std::string& text) {
        out << text << "\n";
    }

    void ConsoleRenderer::writeDivider(std::ostream& out) {
        out << "<--------------------------->\n";
    }

    int ConsoleRenderer::safeInput(int min, int max) {
        int value;
        while (true) {
            if (std::cin >> value && value >= min && value <= max) {
                return value;
            } else {
                std::cin.clear();
                std::cin.ignore(100, '\n');
                std::cout << "Невірне введення!" << std::endl;
            }
        }
    }

    int ConsoleRenderer::mainMenu(std::ostream& out) {
        writeLine(out, "Головне меню");
        writeLine(out, "1. Почати роботу");
        writeLine(out, "2. Вийти");
        return safeInput(1, 2);
    }

    int ConsoleRenderer::additionalOptions(std::ostream& out) {
        writeLine(out, "Додаткові опції:");
        writeDivider(out);
        writeLine(out, "1. Знайти найсильнішу мережу");
        writeLine(out, "2. Знайти найзахищенішу мережу");
        writeLine(out, "3. Повернутись у головне меню");
        writeDivider(out);
        return safeInput(1, 3);
    }


    void ConsoleRenderer::shortRender(const resultAnalyzeList& results, std::ostream& out) {
        writeLine(out, "SHORT MOCK DATA");

        for (const auto& res : results) {
            writeDivider(out);
            writeLine(out, "SSID: " + res.name);
            writeLine(out, "Сигнал: " + res.signalStrength);
            writeLine(out, "Діапазон: " + res.channel);
            writeDivider(out);
        }
    }

    void ConsoleRenderer::fullRender(const resultAnalyzeList& results, std::ostream& out) {
        writeLine(out, "FULL MOCK DATA");

        for (const auto& res : results) {
            writeDivider(out);
            writeLine(out, "SSID: " + res.name);
            writeLine(out, "MAC: " + res.macAddress);
            writeLine(out, "Сигнал: " + res.signalStrength);
            writeLine(out, "Діапазон: " + res.channel);
            writeLine(out, "Безпека: " + res.encryption);

            writeDivider(out);
        }
    }

    int ConsoleRenderer::selectRenderMode(std::ostream& out) {
        writeLine(out, "Оберіть режим:");
        writeLine(out, "1. Повне сканування");
        writeLine(out, "2. Коротке сканування");
        return safeInput(1, 2);
    }

    int ConsoleRenderer::selectScannerMode(std::ostream& out) {
        writeLine(out, "Оберіть режим сканеру:");
        writeLine(out, "1. RealScanner");
        writeLine(out, "2. MockScanner");
        return safeInput(1, 2);
    }
}
