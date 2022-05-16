#include <fstream>
#include <sstream>
#include <filesystem>

#include "dataloader.h"
#include <iostream>


void DataLoader::openDirectory(const string& dirPath) {
    _costsParser.read(dirPath + "/Costs.csv");
    _transportParser.read(dirPath + "/Transport.csv");
    _instituteParser.read(dirPath + "/Institute.csv");
    _caffeCinemaParser.read(dirPath + "/Caffe-and-cinema.csv");
}

string DataLoader::locateDirectory(const string& initialPath, int depth) {
    for (std::filesystem::recursive_directory_iterator i(initialPath), end; i != end; ++i) {
        if (i->path().filename().string()[0] == '.') {
            i.disable_recursion_pending();
            continue;
        }
        if (i->path().filename() == "Caffe-and-cinema.csv") {
            return i->path().parent_path().string();
        }
        if (i.depth() > depth) {
            break;
        }
    }
    return initialPath;
}

uint DataLoader::getOtherCosts(const string& city, uint age) const {
    size_t idx = _costsParser.findFirst(vector<string>({city, std::to_string(age)}));
    return std::stoi(_costsParser[idx][3]);
}

uint DataLoader::getHomeFoodCost(const string& city, uint age) const {
    size_t idx = _costsParser.findFirst(vector<string>({city, std::to_string(age)}));
    return std::stoi(_costsParser[idx][2]);
}

uint DataLoader::getTransportCost(const string& city, const string& address, const string& institute) const {
    vector<string> querry ({city, address, institute});
    size_t idx = _transportParser.findFirst(querry);
    return std::stoi(_transportParser[idx][3]);
}

uint DataLoader::getInstituteDinner(const string& city, const string& institute) const {
    size_t idx = _instituteParser.findFirst(vector<string>({city, institute}));
    return std::stoi(_instituteParser[idx][2]);
}

uint DataLoader::getCinemaCost(const string& city, const string& address, const string& caffe, const string& cinema) const {
    size_t idx = _caffeCinemaParser.findFirst(vector<string>({city, address, caffe, "", cinema}));
    return std::stoi(_caffeCinemaParser[idx][3]);
}

uint DataLoader::getCaffeCost(const string& city, const string& address, const string& caffe, const string& cinema) const {
    size_t idx = _caffeCinemaParser.findFirst(vector<string>({city, address, caffe, "", cinema}));
    return std::stoi(_caffeCinemaParser[idx][5]);
}


CSVParser& DataLoader::costs() {
    return _costsParser;
}

CSVParser& DataLoader::transport() {
    return _transportParser;
}

CSVParser& DataLoader::institute() {
    return _instituteParser;
}

CSVParser& DataLoader::caffeCinema() {
    return _caffeCinemaParser;
}
