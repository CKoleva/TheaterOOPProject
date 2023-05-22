#include "Hall.h"
#include <iostream>

Hall::Hall(const string name,const size_t rows,const size_t seats) : Venue(name), numberOfRows(rows), numberOfSeats(seats) {}

const size_t Hall::getNumberOfRows() const {
    return this->numberOfRows;
}

const size_t Hall::getNumberOfSeats() const {
    return this->numberOfSeats;
}

Hall* Hall::clone() {
    return new Hall(*this);
}