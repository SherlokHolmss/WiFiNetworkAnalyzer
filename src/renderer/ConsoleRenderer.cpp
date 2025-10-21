//
// Created by USER on 11.10.2025.
//
#include <iostream>
#include "ConsoleRenderer.h"
#include "../analyzer/Analyzer.h"


namespace wifi {
    void ConsoleRenderer::render(const netWorkList& networks) {
        std::cout <<"MOCK DATA"<< std::endl;
        for (const auto& network : networks) {
            std::cout <<"<-------------------------->" << std::endl;
            std::cout <<"SSID:" << network.ssid<< std::endl;
            std::cout <<"BSIID:" << network.bssid<< std::endl;
            std::cout <<"Signal:" << network.signalStrength<< std::endl;
            std::cout <<"Channel:" << network.channel<< std::endl;
            std::cout <<"Encryption:" << network.encryption<< std::endl;
            std::cout <<"<-------------------------->" << std::endl;
        }
    }

}