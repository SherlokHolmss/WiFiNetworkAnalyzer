#include "Analyzer.h"
#include "../app/WiFiAnalyzerApp.h"
#include <string>
#include <iostream>
namespace wifi {
    std::string Analyzer::getStrongestNetwork(const wifi::netWorkList &networks) {
        if (networks.empty()) return "Немає доступних мереж";
        int strongest = networks[0].signalStrength;
        std::string strongestSSID = networks[0].ssid;
        for (const auto &network: networks) {
            if (network.signalStrength > strongest) {
                strongestSSID = network.ssid;
            }
        }
        return strongestSSID;
    }
    std::string Analyzer::getMostSecureNetwork(const wifi::netWorkList &networks) {
        if (networks.empty()) return "Немає доступних мереж";
        int strongestSecure = networks[0].encryption;
        std::string strongestSecureSSID = networks[0].ssid;
        for (const auto &network: networks) {
            if (network.encryption > strongestSecure) {
                strongestSecureSSID = network.ssid;
            }
        }
        return strongestSecureSSID;
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
