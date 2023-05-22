#include "Ticket.h"
#include <iostream>

const size_t Ticket::getRow() const { 
    return row;
}

const size_t Ticket::getSeat() const { 
    return seat; 
}

const Event& Ticket::getEvent() const { 
    return event; 
}

Ticket::Ticket(int row, int seat, const Event& event)
    : row(row), seat(seat), event(event) {}


void Ticket::printTicket() const {
    std::cout << "R: " << this->row << ", S: " << this->seat << "\n";
}

Ticket* Ticket::clone() {
    return new Ticket(*this);
}

bool Ticket::operator==(const Ticket& other) {
    return this->event == other.event && this->row == other.row && this->seat == other.seat;
}