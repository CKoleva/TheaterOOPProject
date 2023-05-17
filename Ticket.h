#pragma once
#include "Event.h"

using std::size_t;

class Ticket {
protected:
    size_t row;  
    size_t seat;
    Event event;

public:
    Ticket(int row, int seat, const Event& event); //parametric constuctor

    //Getters
    const size_t getRow() const;
    const size_t getSeat() const;
    const Event& getEvent() const;

    virtual void printTicket() const;
    virtual Ticket* clone();

    virtual ~Ticket() = default;
};