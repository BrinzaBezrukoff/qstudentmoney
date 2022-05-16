#include "student.h"


uint DateUtils::getMonthDays(uint month) {
    uint months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return months[month];
}

uint DateUtils::getWeekendDays(uint month, uint workDays) {
    return getMonthDays(month) - workDays;
}


Student::Student(DataLoader* data, const string& city, const string& address, const string& cinema,
                 const string& caffe, const string& institute, uint age)
{
    _city = city;
    _address = address;
    _cinema = cinema;
    _caffe = caffe;
    _institute = institute;
    _age = age;
    _data = data;
}

uint Student::getWeekendCost() const {
    return _data->getCinemaCost(_city, _address, _caffe, _cinema) + _data->getCaffeCost(_city, _address, _caffe, _cinema);
}

uint Student::getWorkdayCost() const {
    return 2 * _data->getTransportCost(_city, _address, _institute) + _data->getInstituteDinner(_city, _institute);
}

uint Student::getCosts(uint month, uint workdays, bool withAge) const {
    uint costs = workdays * getWorkdayCost() +
                 DateUtils::getWeekendDays(month, workdays) * getWeekendCost();
    if (withAge) {
        costs += _data->getOtherCosts(_city, _age) + _data->getHomeFoodCost(_city, _age);
    }
    return costs;
}

