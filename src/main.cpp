#include <iostream>
#include <fstream>
#include <filesystem>
#include <thread>
#include <userver/components/minimal_server_component_list.hpp>
#include <userver/clients/dns/component.hpp>
#include <userver/clients/http/component.hpp>
#include <userver/server/handlers/ping.hpp>
#include <userver/utils/daemon_run.hpp>

#include "TDirectoryScaner.h"
#include "THttpHandler.h"

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
    auto scanner = std::make_shared<TDirectoryScaner>();
    THttpHandler::SetScanner(scanner);
     std::thread scanner_thread([&scanner, intervalSeconds, directoryPath]() {
        scanner->IntervalScanner(intervalSeconds, directoryPath);
    });
    scanner_thread.detach();
    std::cout<<intervalSeconds<<'\n';
    auto componentList = userver::components::MinimalServerComponentList()
                            .Append<userver::server::handlers::Ping>()
                            .Append<userver::components::HttpClient>()
                            .Append<userver::clients::dns::Component>();

    NHttpHandler::AppendHandler(componentList);
    return userver::utils::DaemonMain(argc, argv, componentList);
}
