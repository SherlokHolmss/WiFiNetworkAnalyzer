//
// Created by USER on 11.10.2025.
//
#include <iostream>
#include "ConsoleRenderer.h"
#include "../analyzer/Analyzer.h"


namespace wifi {
    void ConsoleRenderer::shortRender(const resultAnalyzeList& results) {
        std::cout <<"SHORT MOCK DATA"<< std::endl;
        for (const auto& res : results) {
            std::cout << "SSID: " << res.name << "\n";
            std::cout << "Сигнал: " << res.signalStrength << "\n";
            std::cout << "Безпека: " << res.encryption << "\n";
            std::cout << "---------------------------\n";
        }
    }

    void ConsoleRenderer::fullRender(const resultAnalyzeList& results) {
        std::cout <<"FULL MOCK DATA"<< std::endl;
        for (const auto& res : results) {
            std::cout << "SSID: " << res.name << "\n";
            std::cout << "MAC: " << res.macAddress << "\n";
            std::cout << "Сигнал: " << res.signalStrength << "\n";
            std::cout << "Діапазон: " << res.channel << "\n";
            std::cout << "Безпека: " << res.encryption << "\n";
            std::cout << "---------------------------\n";
        }
    }

}