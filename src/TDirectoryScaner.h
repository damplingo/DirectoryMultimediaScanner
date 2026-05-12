#pragma once
#include <vector>
#include <filesystem>
#include <string>
#include <unordered_set>
#include "json.hpp"

using json = nlohmann::json;
namespace Nfs = std::filesystem;



class TDirectoryScaner{
    private:
    std::unordered_set<std::string> Audio = {".wav", ".mp3", ".flac", ".alac", ".wma", ".aac", "ogg"};
    std::unordered_set<std::string> Video = {".mpg", ".mp4", ".avi",  ".mkv", ".mov", ".wmv", ".flv", ".webm", ".m4v", 
        ".mpeg", ".3gp", ".3g2", ".ogv", ".ts", ".m2ts", ".vob"};
    std::unordered_set<std::string> Images = {".jpeg", ".png", ".svg",".jpg", ".heic", ".avif", ".bmp"};
    public:
    json ScanDirectory(const Nfs::path& path);
    bool WriteReport(const json& info, const std::string& relativePath, const Nfs::path& directory);
    void IntervalScanner(int interval, const Nfs::path& path);
};
