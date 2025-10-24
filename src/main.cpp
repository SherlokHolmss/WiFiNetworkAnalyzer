#include <iostream>


#include "app/WiFiAnalyzerApp.h"

using namespace std;

int main() {
    system("chcp 65001");
    wifi::WifiAnalyzerApp app;
    app.run();
    return 0;
}
