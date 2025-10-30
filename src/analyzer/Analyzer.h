//
// Created by USER on 11.10.2025.
//

#ifndef WIFINETWORKANALYZER_ANALYZER_H
#define WIFINETWORKANALYZER_ANALYZER_H
#endif //WIFINETWORKANALYZER_ANALYZER_H


#pragma once
#include "../utils/Types.h"
#include <string>
namespace wifi {
    class Analyzer {
    public:
        resultAnalyzeList analyze(const wifi::netWorkList &networks);
        void printSummary(const netWorkList& networks);
        std::string getStrongestNetwork(const wifi::netWorkList &networks);
        std::string getMostSecureNetwork(const wifi::netWorkList &networks);
        std::string getMainCharacteristics(const wifi::netWorkList &networks);
    private:
        std::string analyzeSignal(int strength);
        std::string analyzeChannel(int channel);
        std::string analyzeEncryption(int encryption);

    };
}
