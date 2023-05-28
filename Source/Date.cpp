#include "../Headers/Date.h"
#include <iomanip>

Date::Date(size_t year, size_t month, size_t day)
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
    char delimiter1;
    char demiliter2;
    ss >> this->year >> delimiter1 >> this->month >> demiliter2 >> this->day;

    // Check if the date string is valid
    if (ss.fail() || delimiter1 != '-' || demiliter2 != '-' || !isValidDate()) {
        throw std::runtime_error("Invalid date string: " + data);
    }
}

bool Date::isValidDate() const {
    // Check if the year, month, and day values are within valid ranges
    if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31) {
        return false;
    }

    // Check for leap years
    bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    if (month == 2 && (isLeapYear && day > 29 || !isLeapYear && day > 28)) {
        return false;
    }

    // Check for months with 30 days
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
        return false;
    }

    return true;
}