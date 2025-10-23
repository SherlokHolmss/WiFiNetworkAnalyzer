//
// Created by USER on 11.10.2025.
//
#include <iostream>
#include "ConsoleRenderer.h"
#include "../analyzer/Analyzer.h"


namespace wifi {
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
            case 2:
                shortRender(results);
        }
    }
}
