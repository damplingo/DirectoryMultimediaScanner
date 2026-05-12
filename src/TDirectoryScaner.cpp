#include "TDirectoryScaner.h"

#include <iostream>
#include <vector>
#include <filesystem>
#include <utility>
#include <ranges>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <chrono>
#include <thread>

void TDirectoryScaner::IntervalScanner(int interval, const Nfs::path& path){

    while (true) {
        if (!Nfs::exists(path)) {
            std::cerr<<"Error: Directory " <<path.string()<<" does not exist\n";
            return;
        }
        if (!Nfs::is_directory(path)) {
            std::cerr<<"Error: "<<path.string()<<" is not a directory\n";
            return;
        
        }
        json report = ScanDirectory(path);
        if (WriteReport(report, ".media_files", path)) {
            std::string filePath = "~/"+path.string()+"/.media_files";
            std::cout<<"File update: "<<filePath<<'\n';
        }
        
        std::this_thread::sleep_for(std::chrono::seconds(interval));
    }
}

bool TDirectoryScaner::WriteReport(const json& info, const std::string& relativePath, const Nfs::path& directory) {

    Nfs::path file_path = directory / relativePath;
    try {
        std::ofstream file(file_path);
         if (!file) {
            std::cerr << "Report file not available" << file_path << std::endl;
            return false;
        }
        file << info.dump(4);
        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Error in write report: " << e.what() << std::endl;
        return false;
    }
}


json TDirectoryScaner::ScanDirectory(const Nfs::path& path) {
    json report;
    report["audio"] = json::array();
    report["video"] = json::array();
    report["images"] = json::array();
    try {  
        for (const auto& entry : Nfs::directory_iterator(path)) {
            if (!entry.is_regular_file()) continue;

            std::string ext = entry.path().extension().string();
            std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
            std::string filename = entry.path().filename().string();

            if (Audio.count(ext)) {
                report["audio"].push_back(filename);
            } else if (Video.count(ext)) {
                report["video"].push_back(filename);
            } else if (Images.count(ext)) {
                report["images"].push_back(filename);
            }
        }
    }          
    catch (const Nfs::filesystem_error& ex) {
        std::cerr<<"Filesystem error scanning directory "<<ex.what()<<" \n";
    } catch (const std::exception& ex) {
        std::cerr<<"Error scanning directory "<<ex.what()<<" \n";
    }
    return report;    
}

