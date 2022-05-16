#ifndef __STUDENT_H
#define __STUDENT_H

#include <string>
#include "dataloader.h"

typedef unsigned int uint;
using std::string;


namespace DateUtils {
    uint getMonthDays(uint month);
    uint getWeekendDays(uint month, uint workDays);
}


class Student {
private:
    string _city;
    string _address;
    string _cinema;
    string _caffe;
    string _institute;
    uint _age;

    DataLoader* _data;

public:
    explicit Student(DataLoader* data, const string& city, const string& address, const string& cinema,
                     const string& caffe, const string& institute, uint age);

    uint getWeekendCost() const;
    uint getWorkdayCost() const;

    uint getCosts(uint month, uint workdays, bool withAge = true) const;
};

#endif
