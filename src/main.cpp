#include <iostream>
#include <fstream>
#include <filesystem>
#include <thread>
#include <getopt.h>
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
    std::string path = std::getenv("HOME");
    static struct option long_options[] = {
        {"config",      required_argument, 0, 'c'},
        {0, 0, 0, 0}
    };
    int opt;
    int option_index = 0;
    int new_argc = 1;
    while ((opt = getopt_long(argc, argv, "i:d:",long_options,  &option_index)) != -1) {
        switch (opt) {
            case 'd':
                path = optarg;
                break;
            case 'i':
                try {
                    intervalSeconds = std::stoi(optarg);
                    if (intervalSeconds <= 0) {
                        std::cerr << "Error: Interval must be an integer\n";
                        return 1;
                    }
                }
                catch(...) {
                    std::cerr<<"Error: Input interval error\n";
                    return 1;
                }
                break;
            case 'c':
                argv[new_argc++] = argv[optind - 2]; // опция
                argv[new_argc++] = argv[optind - 1];
                break;
            default:
                std::cout<< opt<<" is unknown param\n";
                return 1;
        }
    }
    for (int i = optind; i < argc; ++i) {
        argv[new_argc++] = argv[i];
    }

    argv[new_argc] = nullptr;
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
    return userver::utils::DaemonMain(new_argc, argv, componentList);
}
