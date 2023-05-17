#pragma once
#include"Venue.h"
#include "Date.h"

class Event : public Venue {
private:
    Date date;
    string hallName;

public:
    Event(const string& name, const Date& date, const string& hallName);

    // Getters
    const string& getName() const;
    const Date& getDate() const;
    const string& getHallName() const;

    bool operator==(const Event& other) const; //operator== for comparing Event objects

    Event* clone();
};