#include "BookedTicket.h"
#include <iostream>

const string& BookedTicket::getNote() const {
    return this->note;
}

BookedTicket::BookedTicket(int row, int seat, const Event& event, const string note)
    : Ticket(row, seat, event) , note(note) {}

Ticket* BookedTicket::clone() {
    return new BookedTicket(*this);
}