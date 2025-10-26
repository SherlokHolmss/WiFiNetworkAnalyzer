#include <iostream>
#include "Analyzer.h"
#include "../utils/Logger.h"
#include <string>

namespace wifi {
    std::string Analyzer::getStrongestNetword(const netWorkList &networks) {
        Logger logger;
        int strongest = networks[0].signalStrength;
        std::string strongestSSID = "";
        for (const auto &network: networks) {
            if (network.signalStrength > strongest) {
                strongestSSID = network.ssid;
            }
        }
        logger.info("Найсильніша мережа-");
        return strongestSSID;
    }

    std::string Analyzer::analyzeSignal(int strength) {
        if (strength < -60)
            return "Сигнал слабкий";
        else if (strength < -40)
            return "Сигнал середній";
        else
            return "Сигнал сильний";
    }

    std::string Analyzer::analyzeChannel(int channel) {
        return (channel <= 13) ? "2.4GHz" : "5GHz";
    }

    std::string Analyzer::analyzeEncryption(int encryption) {
        switch (encryption) {
            case 1:
                return "Мережа не захищена!";
                break;
            case 2:
                return "Мережа захищена погано";
                break;
            case 3:
                return "Мережа захищена добре";
                break;
            default:
                return "Невідомо";
        }
    }


    resultAnalyzeList Analyzer::analyze(const netWorkList &networks) {
        resultAnalyzeList results;
        for (const auto &network: networks) {
            resultAnalyze result;
            result.name = network.ssid;
            result.macAddress = network.bssid;
            result.signalStrength = analyzeSignal(network.signalStrength);
            result.channel = analyzeChannel(network.channel);
            result.encryption = analyzeEncryption(network.encryption);

            results.push_back(result);
        }

        return results;
    }
}
