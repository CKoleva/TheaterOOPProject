#include "Event.h"

Event::Event(const string& name, const Date& date, const std::string& hallName)
    : Venue(name), date(date), hallName(hallName) {}

const string& Event::getName() const {
    return this->name;
}

const Date& Event::getDate() const {
    return this->date;
}

const std::string& Event::getHallName() const {
    return this->hallName;
}

bool Event::operator==(const Event& other) const {
    return name == other.name && date == other.date && hallName == other.hallName;
}

Event* Event::clone() {
    return new Event(*this);
}