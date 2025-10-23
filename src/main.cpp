#include <iostream>

#include "scanner/ScannerMock.h"
#include "analyzer/Analyzer.h"
#include "renderer/ConsoleRenderer.h"
#include "string"

using namespace std;

int userOption = 0;

int main() {
    system("chcp 65001");
    wifi::ScannerMock scanner;
    wifi::Analyzer analyzer;
    wifi::ConsoleRenderer renderer;
    auto networks = scanner.scanNetworks();

    auto analyzed = analyzer.analyze(networks);

    wifi::ConsoleRenderer::selectRenderMode();


    return 0;
}
