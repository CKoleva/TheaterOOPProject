#include "Theater.h"
#include <iostream>
#include <locale>
#include <algorithm>

void Theater::addHall(Hall* hall) {
    halls.push_back(hall->clone());
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

Event* Theater::findEvent(const string& eventName, const Date& date) const {
    for (const auto& e : events) {
        if (e->getName() == eventName && e->getDate() == date) {
            return e;
        }
    }
    
    throw std::runtime_error("Event not found.\n");
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

bool Theater::isSeatAvailable(const Event& event, const size_t row, const size_t seat) const {

    // Find the hall by name
    Hall* hall = findHallByName(event.getHallName());

    // Check if the seat is valid
    if (row < 1 || row > hall->getNumberOfRows() || seat < 1 || seat > hall->getNumberOfSeats()) {
        throw std::runtime_error("Invalid seat.\n");
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
            return true; // Code is valid
        }
    }
    return false; // Code is not registered
}

void Theater::addEvent(const Date& date, const std::string& hallName, const std::string& eventName) {
    // Find the hall by name
    Hall* hall = findHallByName(hallName);
    if (hall == nullptr) {
        throw std::runtime_error("Hall not found.\n");
    }

    // Check if the hall is free on this date or if this event is already scheduled on this day in another hall  
    for (const Event* event : events) {
        if (event->getDate() == date && event->getHallName() == hallName) {
            throw std::runtime_error("An event is already scheduled in Hall " + hallName + " on " + date.serialize() + ".\n");
        }
        else if (event->getName() == eventName && event->getDate() == date)
        {
            throw std::runtime_error("This event is already scheduled on " + date.serialize() + " in Hall " + event->getHallName() + ".\n");    //can't have the same event on the same day because of book/unbook
        }   
    }

    // Create a new Event object
    Event* event = new Event(eventName, date, hallName);

    // Add the event to the events vector
    events.push_back(event->clone());
}


void Theater::bookTicket(const size_t row, const size_t seat, const Date& date, const string& eventName, const string note) {
    Event* foundEvent = findEvent(eventName, date);

    if (isSeatAvailable(*foundEvent, row, seat)) {
        // Seat is available, create a new BookedTicket object
        BookedTicket* toBook = new BookedTicket(row, seat, *foundEvent, note);

        // Add the ticket to the bookedTickets vector ordered by events
        size_t i = 0;
        while (i < bookedTickets.size() && !(bookedTickets[i]->getEvent() == *foundEvent)) {
            ++i;
        }
        
        bookedTickets.insert(bookedTickets.begin() + i, toBook->clone());

        // Remove the ticket from the freeTickets vector
        removeFreeTicket(*foundEvent, row, seat);
    }
}


void Theater::purchaseTicket(const size_t row, const size_t seat, const Date& date, const string& eventName) {
    Event* foundEvent = findEvent(eventName, date);
    if (isSeatAvailable(*foundEvent, row, seat)) {
        // Seat is available, create a new PurchasedTicket object
        PurchasedTicket* purchasedTicket = new PurchasedTicket(row, seat, *foundEvent);

        // Add the PurchasedTicket to the purchasedTickets vector
        purchasedTickets.push_back(purchasedTicket->clone());                    

        // Remove the Ticket from the freeTickets vector
        removeFreeTicket(*foundEvent, row, seat);
    }
}


void Theater::unbookTicket(const size_t row, const size_t seat, const Date& date, const string& eventName) {
    // Find the event
    Event* foundEvent = findEvent(eventName, date);

    // Check if the seat is valid
    Hall* hall = findHallByName(foundEvent->getHallName());

    if (row < 1 || row > hall->getNumberOfRows() || seat < 1 || seat > hall->getNumberOfSeats()) {
        throw std::runtime_error("Invalid seat.\n");
    }

    // Find the booked ticket for unbooking
    BookedTicket* bookedTicket = nullptr;
    for (size_t i = 0; i < bookedTickets.size(); ++i) {
        BookedTicket* ticket = bookedTickets[i];
        if (ticket->getEvent() == *foundEvent && ticket->getRow() == row && ticket->getSeat() == seat) {    
            bookedTicket = ticket;                                                                          
            bookedTickets.erase(bookedTickets.begin() + i);
            break;
        }
    }

    if (bookedTicket == nullptr) {
        throw std::runtime_error("Ticket not found.\n");
    }

    // Add the booked ticket back to the freeTickets vector
    addFree((Ticket*)bookedTicket);
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

    if (!std::all_of(row.begin(), row.end(), ::isdigit) 
        || !std::all_of(seat.begin(), seat.end(), ::isdigit)
        || !std::all_of(suffix.begin(), suffix.end(), ::isdigit)
        || letterS != 'S'
        || letterD != 'D'
        || suffix[0] == 0)
    {
        std::cout << "here\n"; 
        throw std::invalid_argument("Invalid code format");
    }

    if (validateUniqueCode(code)) {
        std::cout << "Valid code. Ticket is on row " << std::stoi(row) << " and seat " << std::stoi(seat) << std::endl;
    } else {
        std::cout << "Valid code. This ticket is not purchased!\n"; // Format is valid 
    }                                                          //but there is no information of purchased ticket with this code
    
}

void Theater::displayAvailableSeats(const string& eventName, const Date& date) const {            
    // Find the event                                                                 
    Event* foundEvent = findEvent(eventName, date);

    std::cout << "Free seats for event \"" << foundEvent->getName() << "\" on " << date.serialize() << ".\n";
    
    for (const auto& ticket : freeTickets) {
        if (ticket->getEvent() == *foundEvent && ticket->getEvent().getDate() == date) {
            ticket->printTicket();
        }
    }
}

void Theater::displayBookings(const Date& date, const string& eventName) const {       
    // Find the event
    Event* foundEvent = findEvent(eventName, date);

    std::cout << "Booked tickets for event \"" << foundEvent->getName() << "\" on " << date.serialize() << ".\n";
    
    for (const auto& ticket : bookedTickets) {
        if (ticket->getEvent() == *foundEvent && ticket->getEvent().getDate() == date) {
            ticket->printTicket();
        }
    }
}

void Theater::displayBookings(const Date& date) const {
    std::cout << "Bookings on " << date.serialize() << ":" << std::endl;            // needes check first
                                                                                    
    for (const auto& ticket : bookedTickets) {                                      //sorted by events?
        if (ticket->getEvent().getDate() == date) {
            std::cout << "Event \"" + ticket->getEvent().getName() + "\", "; 
            ticket->printTicket();
        }
    }
}

void Theater::displayBookings(const string& eventName) const {
    std::cout << "Bookings for \"" + eventName + "\":\n";

    for (const auto& ticket : bookedTickets)
    {
        if(ticket->getEvent().getName() == eventName) {
            std::cout << "(" + ticket->getEvent().getDate().serialize() + ") ";
            ticket->printTicket();
        }
    }
    
}

Theater::~Theater() {
    free();
}

void Theater::free() {
    for (Hall* hall : halls) {
        delete hall;
    }
    halls.clear();

    for (Event* event : events) {
        delete event;
    }
    events.clear();

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

