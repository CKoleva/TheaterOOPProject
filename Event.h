#pragma once
#include"Venue.h"
#include "Date.h"

class Event : public Venue {
private:
    Date date;
    string hallName;
    size_t purchasedTickets;

public:
    Event(const string& name, const Date& date, const string& hallName);

    // Getters
    const string& getName() const;
    const Date& getDate() const;
    const string& getHallName() const;
    const size_t getPurchasedTicketsCount() const;

    bool operator==(const Event& other) const; //operator== for comparing Event objects
    void increasePTCount(); // Increasing purchased tickets' count by one

    Event* clone();
};