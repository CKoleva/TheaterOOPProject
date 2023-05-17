#include "Date.h"
#include <iomanip>

Date::Date(size_t day, size_t month, size_t year)
    : year(year), month(month), day(day) {
}

Date::Date(const string dateStr) {
    this->deserialize(dateStr);
}

int Date::getYear() const {
    return year;
}

int Date::getMonth() const {
    return month;
}

int Date::getDay() const {
    return day;
}

bool Date::operator==(const Date& other) const {
    return (year == other.year) && (month == other.month) && (day == other.day);
}

bool Date::operator!=(const Date& other) const {
    return !(*this == other);
}

bool Date::operator<(const Date& other) const {
    if (year < other.year)
        return true;
    if (year > other.year)
        return false;
    if (month < other.month)
        return true;
    if (month > other.month)
        return false;
    return day < other.day;
}

bool Date::operator<=(const Date& other) const {
    return (*this < other) || (*this == other);
}

bool Date::operator>(const Date& other) const {
    return !(*this <= other);
}

bool Date::operator>=(const Date& other) const {
    return !(*this < other);
}

const string Date::serialize() const {
    stringstream ss;
    ss << this->year << "-" << std::setfill('0') << std::setw(2) << this->month << "-" << std::setw(2) << day;
    return ss.str();
}

void Date::deserialize(const string& data) {
    stringstream ss(data);
    char delimiter;
    ss >> this->year >> delimiter >> this->month >> delimiter >> this->day;
}    