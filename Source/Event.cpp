#include "../Headers/Event.h"

Event::Event(const string& name, const Date& date, const string& hallName)
    : Venue(name), date(date), hallName(hallName), purchasedTickets(0) {}

const string& Event::getName() const {
    return this->name;
}

const Date& Event::getDate() const {
    return this->date;
}

const string& Event::getHallName() const {
    return this->hallName;
}

const size_t Event::getPurchasedTicketsCount() const {
    return this->purchasedTickets;
}

bool Event::operator==(const Event& other) const {
    return name == other.name && date == other.date;    //no need to ckeck hall because an event can only be in one hall per day
}

void Event::increasePTCount() {
    ++this->purchasedTickets;
}

Event* Event::clone() {
    return new Event(*this);
}