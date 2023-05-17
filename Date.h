#pragma once
#include "ISerializable.h"
#include <cstddef>

using std::size_t;

class Date : public ISerializable {
private:
    int year;
    int month;
    int day;

public:
    Date(size_t day, size_t month, size_t year);

    // Getters
    int getYear() const;
    int getMonth() const;
    int getDay() const;

    // Comparison methods
    bool operator==(const Date& other) const;
    bool operator!=(const Date& other) const;
    bool operator<(const Date& other) const;
    bool operator<=(const Date& other) const;
    bool operator>(const Date& other) const;
    bool operator>=(const Date& other) const;

    const string serialize() const override final; //serialize the Date object

    void deserialize(const string& data) override final; //deserialize the string and set the Date object's state
};