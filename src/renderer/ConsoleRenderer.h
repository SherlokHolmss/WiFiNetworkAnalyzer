//
// Created by USER on 11.10.2025.
//

#ifndef WIFINETWORKANALYZER_CONSOLERENDERER_H
#define WIFINETWORKANALYZER_CONSOLERENDERER_H

#endif //WIFINETWORKANALYZER_CONSOLERENDERER_H
#pragma once
#include "../utils/Types.h"


namespace wifi {
    class ConsoleRenderer {
    private:
        void write(std::ostream& out, const std::string& text);
        void writeLine(std::ostream& out, const std::string& text);
        void writeDivider(std::ostream& out);

    public:
        int safeInput(int min, int max);

        int mainMenu(std::ostream& out);
        int additionalOptions(std::ostream& out);
        int selectRenderMode(std::ostream& out);
        int selectScannerMode(std::ostream& out);

        void shortRender(const resultAnalyzeList& results, std::ostream& out);
        void fullRender(const resultAnalyzeList& results, std::ostream& out);
    };
}
