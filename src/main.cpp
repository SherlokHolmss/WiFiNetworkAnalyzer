#include <iostream>

#include "scanner/ScannerMock.h"
#include "analyzer/Analyzer.h"
#include "renderer/ConsoleRenderer.h"
#include "string"

using namespace std;

int userOption;

int main() {
    system("chcp 65001");
    wifi::ScannerMock scanner;
    wifi::Analyzer analyzer;
    wifi::ConsoleRenderer renderer;
    auto networks = scanner.scanNetworks();

    auto analyzed = analyzer.analyze(networks);

    cout << "Оберіть режим:" << endl;
    cout << "1.Повне сканування" << endl;
    cout << "1.Коротке сканування" << endl;
    cin >> userOption;
    switch (userOption) {
        case '1':
            renderer.fullRender(analyzed);
        case '2':
            renderer.shortRender(analyzed);
        default:
            renderer.fullRender(analyzed);
    }


    return 0;
}
