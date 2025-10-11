cmake_minimum_required(VERSION 4.0)
project(WiFiNetworkAnalyzer)

set(CMAKE_CXX_STANDARD 20)

add_executable(WiFiNetworkAnalyzer main.cpp
        src/scanner.h
        src/analyzer.h
        src/renderer.h
        src/utils.h)
