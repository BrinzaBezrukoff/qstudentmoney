#ifndef __DATALOADER_H
#define __DATALOADER_H

#include <string>
#include "csvparser.h"

typedef unsigned int uint;
using std::string;


class DataLoader {
public:
    DataLoader() = default;

    void openDirectory(const string& dirPath);

    static string locateDirectory(const string& initialPath, int depth = 20);

    uint getOtherCosts(const string& city, uint age) const;
    uint getHomeFoodCost(const string& city, uint age) const;
    uint getTransportCost(const string& city, const string& address, const string& institute) const;
    uint getInstituteDinner(const string& city, const string& institute) const;
    uint getCinemaCost(const string& city, const string& address, const string& caffe, const string& cinema) const;
    uint getCaffeCost(const string& city, const string& address, const string& caffe, const string& cinema) const;

    CSVParser& costs();
    CSVParser& transport();
    CSVParser& institute();
    CSVParser& caffeCinema();

private:
    CSVParser _costsParser;
    CSVParser _transportParser;
    CSVParser _instituteParser;
    CSVParser _caffeCinemaParser;

};


#endif
