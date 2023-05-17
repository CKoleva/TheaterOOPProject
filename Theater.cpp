#include "Theater.h"
#include <iostream>
#include <locale>
#include <algorithm>

void Theater::addHall(Hall* hall) {
    halls.push_back(hall->clone());
}

Event& Theater::getEvent(const size_t idx) const {
    return *this->events[idx];
}

void Theater::addFree(Ticket* t) {
    this->freeTickets.push_back(t->clone());
}


Theater::Theater() {}

Theater* Theater::instance = nullptr;

Theater* Theater::getInstance() {
    if (instance == nullptr) {
        instance = new Theater();
    }
    return instance;
}

// Getters
const std::vector<Hall*>& Theater::getHalls() const {
    return halls;
}

const std::vector<Event*>& Theater::getEvents() const {
    return events;
}

const std::vector<BookedTicket*>& Theater::getBookedTickets() const {
    return bookedTickets;
}

const std::vector<Ticket*>& Theater::getFreeTickets() const {
    return freeTickets;
}

const std::vector<PurchasedTicket*>& Theater::getPurchasedTickets() const {
    return purchasedTickets;
}

Event* Theater::findEvent(const Event& event) const {
    for (const auto& e : events) {
        if (*e == event) {
            return e;
        }
    }
    return nullptr;
}

Hall* Theater::findHallByName(const std::string& name) const {
    for (const auto& hall : halls) {
        if (hall->getName() == name) {
            return hall;
        }
    }
    return nullptr;
}

void Theater::removeFreeTicket(const Event& event, size_t row, size_t seat) {
    for (auto it = freeTickets.begin(); it != freeTickets.end(); ++it) {
        if ((*it)->getEvent() == event && (*it)->getRow() == row && (*it)->getSeat() == seat) {
            delete *it;
            freeTickets.erase(it);
            break;
        }
    }
}

bool Theater::isSeatAvailable(const Event& event, size_t row, size_t seat) const {
    // Check if the event exists
    Event* foundEvent = findEvent(event);
    if (foundEvent == nullptr) {
        throw std::runtime_error("Event not found.");
    }

    // Find the hall by name
    Hall* hall = findHallByName(event.getHallName());
    if (hall == nullptr) {
        throw std::runtime_error("Hall not found.");
    }

    // Check if the seat is valid
    if (row < 1 || row > hall->getNumberOfRows() || seat < 1 || seat > hall->getNumberOfSeats()) {
        throw std::runtime_error("Invalid seat.");
    }

    // Check if the seat is available
    for (const Ticket* ticket : freeTickets) {
        if (ticket->getEvent() == event && ticket->getRow() == row && ticket->getSeat() == seat) {
            return true; // Seat is available
        }
    }

    return false; // Seat is not available
}

bool Theater::validateUniqueCode(const string& code) const {
    for (const PurchasedTicket* ticket : purchasedTickets) {
        if (ticket->getUniqueCode() == code) {
            return true; // Code is not unique
        }
    }
    return false; // Code is unique
}

void Theater::addEvent(const Date& date, const std::string& hallName, const std::string& eventName) {
    // Find the hall by name
    Hall* hall = findHallByName(hallName);
    if (hall == nullptr) {
        throw std::runtime_error("Hall not found.");
    }

    // Check if the hall is free on this date
    for (const Event* event : events) {
        if (event->getDate() == date && event->getHallName() == hallName) {
            throw std::runtime_error("Event already exists with on this date and in this hall.");
        }
    }

    // Create a new Event object
    Event* event = new Event(eventName, date, hallName);

    // Add the event to the events vector
    events.push_back(event);
}


bool Theater::bookTicket(const Event& event, size_t row, size_t seat, const string note) {
    if (isSeatAvailable(event, row, seat)) {
        // Seat is available, create a new BookedTicket object
        BookedTicket* toBook = new BookedTicket(row, seat, event, note);

        // Add the ticket to the bookedTickets vector ordered by events
        size_t i = 0;
        while (i < bookedTickets.size() && !(bookedTickets[i]->getEvent() == event)) {
            ++i;
        }
        
        bookedTickets.insert(bookedTickets.begin() + i, toBook);            //why not clone()

        // Remove the ticket from the freeTickets vector
        removeFreeTicket(event, row, seat);

        std::cout << "Ticket booked successfully." << std::endl;
        return true; // Ticket booked successfully
    }

    return false; // Seat is not available
}


bool Theater::purchaseTicket(const Event& event, size_t row, size_t seat) {
    if (isSeatAvailable(event, row, seat)) {
        // Seat is available, create a new PurchasedTicket object
        PurchasedTicket* purchasedTicket = new PurchasedTicket(row, seat, event);

        // Add the PurchasedTicket to the purchasedTickets vector
        purchasedTickets.push_back(purchasedTicket);                    //why not clone()

        // Remove the Ticket from the freeTickets vector
        removeFreeTicket(event, row, seat);

        std::cout << "Ticket purchased successfully." << std::endl;
        return true; // Ticket purchased successfully
    }

    return false; // Seat is not available
}


bool Theater::unbookTicket(const Event& event, size_t row, size_t seat) {
    // Find the event
    Event* foundEvent = findEvent(event);
    if (foundEvent == nullptr) {
        throw std::runtime_error("Event not found.");
    }

    // Check if the seat is valid
    Hall* hall = findHallByName(foundEvent->getHallName());
    if (hall == nullptr) {
        throw std::runtime_error("Hall not found.");
    }

    if (row < 1 || row > hall->getNumberOfRows() || seat < 1 || seat > hall->getNumberOfSeats()) {
        throw std::runtime_error("Invalid seat.");
    }

    // Find the booked ticket for unbooking
    BookedTicket* bookedTicket = nullptr;
    for (size_t i = 0; i < bookedTickets.size(); ++i) {
        BookedTicket* ticket = bookedTickets[i];
        if (ticket->getEvent() == *foundEvent && ticket->getRow() == row && ticket->getSeat() == seat) {    //may need a function
            bookedTicket = ticket;                                                                          //also used for purchasing
            bookedTickets.erase(bookedTickets.begin() + i);
            break;
        }
    }

    if (bookedTicket == nullptr) {
        throw std::runtime_error("Ticket not found.");
    }

    // Add the booked ticket back to the freeTickets vector
    freeTickets.push_back(bookedTicket->clone());               //clone() ??

    std::cout << "Ticket unbooked successfully." << std::endl;
    return true;
}


void Theater::check(const string& code) const {
    if (code.size() != 14 || code.substr(0, 2) != "TR")
    {
        throw std::invalid_argument("Invalid code format");
    }

    string row, seat, suffix;
    char letterS, letterD;

    row = code.substr(2, 3);                            //TR002S021D7586
    seat = code.substr(6, 3);
    suffix = code.substr(10);
    letterS = code[5];
    letterD = code[9];

    if (!std::all_of(seat.begin(), row.end(), ::isdigit) 
        || !std::all_of(seat.begin(), seat.end(), ::isdigit)
        || !std::all_of(seat.begin(), seat.end(), ::isdigit)
        || letterS != 'S'
        || letterD != 'D'
        || suffix[0] == 0)
    {
        throw std::invalid_argument("Invalid code format");
    }

    if (validateUniqueCode(code)) {
        std::cout << "Valid code. Ticket is on row " << std::stoi(row) << " and seat " << std::stoi(seat) << std::endl;
    } else {
        std::cout << "Valid code. This ticket is not purchased!\n"; // Format is valid 
    }                                                          //but there is no information of purchased ticket with this code
    
}

void Theater::displayAvailableSeats(const Event& event, const Date& date) const {            //date is not needed as parameter
    // Find the event                                                                  //maybe engine does the work and passes only event
    Event* foundEvent = findEvent(event);
    if (foundEvent == nullptr) {
    throw std::runtime_error("Event not found.");
    }

    std::cout << "Free seats for event \"" << event.getName() << "\" on " << date.serialize() << ":\n";
    
    for (const auto& ticket : freeTickets) {
        if (ticket->getEvent() == event && ticket->getEvent().getDate() == date) {
            ticket->printTicket();
        }
    }
}

void Theater::displayBookings(const Event& event, const Date& date) const {       //too much similar code
    // Find the event
    Event* foundEvent = findEvent(event);
    if (foundEvent == nullptr) {
    throw std::runtime_error("Event not found.");
    }

    std::cout << "Booked tickets for event \"" << event.getName() << "\" on " << date.serialize() << ":\n";
    
    for (const auto& ticket : bookedTickets) {
        if (ticket->getEvent() == event && ticket->getEvent().getDate() == date) {
            ticket->printTicket();
        }
    }
}

void Theater::displayBookings(const Date& date) const {
    std::cout << "Bookings on " << date.serialize() << ":" << std::endl;            // needes check first
                                                                                    
    for (const auto& ticket : bookedTickets) {                                      //sorted by events?
        if (ticket->getEvent().getDate() == date) {
            ticket->printTicket();
        }
    }
}

Theater::~Theater() {
    free();
}

void Theater::free() {
    for (Ticket* ticket : freeTickets) {
        delete ticket;
    }
    freeTickets.clear();

    for (Ticket* ticket : bookedTickets) {
        delete ticket;
    }
    bookedTickets.clear();
    
    for (Ticket* ticket : purchasedTickets) {
        delete ticket;
    }
    purchasedTickets.clear();
}
