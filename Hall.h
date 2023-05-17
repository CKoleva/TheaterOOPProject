#pragma once
#include "Venue.h"

class Hall : public Venue {
private:
    size_t numberOfRows, numberOfSeats;

public: 
    Hall(const string name, const size_t rows, const size_t seats); //Parametric constructor

    //Getters
    const size_t getNumberOfRows() const;
    const size_t getNumberOfSeats() const;

    Hall* clone();
};
