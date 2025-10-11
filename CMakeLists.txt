cmake_minimum_required(VERSION 4.0)
project(WiFiNetworkAnalyzer)

set(CMAKE_CXX_STANDARD 20)

add_executable(WiFiNetworkAnalyzer src/main.cpp
        src/scanner/ScannerMock.cpp
        src/analyzer/Analyzer.cpp
        src/analyzer/Analyzer.h
        src/renderer/ConsoleRenderer.cpp
        src/renderer/ConsoleRenderer.h
        src/scanner/ScannerMock.h
)
