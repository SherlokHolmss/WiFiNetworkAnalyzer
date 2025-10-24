#include <iostream>


#include "app/WiFiAnalyzerApp.h"
#include "scanner/ScannerMock.h"

using namespace std;

int main() {
    system("chcp 65001");
    wifi::ScannerMock scanner;
    wifi::Analyzer analyzer;
    wifi::ConsoleRenderer renderer;

    wifi::WifiAnalyzerApp app(&scanner, &analyzer, &renderer);
    app.run();
    return 0;
}
