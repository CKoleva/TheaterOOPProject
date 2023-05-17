#include "Venue.h"

Venue::Venue(const string& name)
    : name(name) {}

const string& Venue::getName() const {
    return name;
}