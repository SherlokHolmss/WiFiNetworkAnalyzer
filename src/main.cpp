#include <iostream>

#include "scanner/ScannerMock.h"
#include "analyzer/Analyzer.h"
#include "renderer/ConsoleRenderer.h"
using namespace std;

int main() {
    system("chcp 65001");
    wifi::ScannerMock scanner;
    wifi::Analyzer analyzer;
    wifi::ConsoleRenderer renderer;

    auto networks = scanner.scanNetworks();

    auto analyzed = analyzer.analyze(networks);

    renderer.render(analyzed);
    return 0;
}
