#include <iostream>
#include <fstream>
#include <filesystem>

#include "TDirectoryScaner.h"

namespace Nfs = std::filesystem;
int main(int argc, char** argv) {
    int intervalSeconds = 25;
    const char* path = std::getenv("HOME");
    if (argc > 1) {
        try {
            intervalSeconds = std::stoi(argv[1]);
            if (intervalSeconds <= 0) {
                std::cerr << "Interval must be an integer\n";
                return 1;
            }
        }
        catch(...) {
            std::cerr<<"Input interval error\n";
            return 1;
        }
    }
    if (argc > 2) {
        path = argv[2];
    }
    Nfs::path directoryPath(path);
    TDirectoryScaner scanner;
    std::cout<<intervalSeconds<<'\n';
    scanner.IntervalScanner(intervalSeconds, directoryPath);
    return 0;
}
