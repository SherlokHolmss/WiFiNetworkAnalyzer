#include <iostream>

#include "scanner/ScannerMock.h"
#include "analyzer/Analyzer.h"
#include "renderer/ConsoleRenderer.h"
#include "app/WiFiAnalyzerApp.h"
#include <string>

using namespace std;

int userOption = 0;

int main() {
    system("chcp 65001");
    wifi::WifiAnalyzerApp app;
    app.run();




    return 0;
}
