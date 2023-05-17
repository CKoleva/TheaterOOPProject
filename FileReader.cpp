#include "FileReader.h"


void FileReader::loadTheaterData(Theater& theater, const std::string& filename) {  //can be separated in smaller functions
    std::ifstream file(filename);                                                   //similar code when loading tickets
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open the file: " + filename);
    }
    json jsonData;
    file >> jsonData;
    file.close();
    // Load halls
    for (const auto& hallData : jsonData["halls"]) {
        std::string name = hallData["name"];
        size_t numRows = hallData["numRows"];
        size_t numSeats = hallData["numSeats"];
        Hall* hall = new Hall(name, numRows, numSeats);     // should it create an object and pass it to addHall
        theater.addHall(hall);
    }

    // Load events
    for (const auto& eventData : jsonData["events"]) {
        Date date(eventData["date"]);
        std::string hallName = eventData["hallName"];
        std::string eventName = eventData["eventName"];
        theater.addEvent(date, hallName, eventName);
    }

    // Load booked tickets
    for (const auto& bookedTicketData : jsonData["bookedTickets"]) {
        size_t row = bookedTicketData["row"];
        size_t seat = bookedTicketData["seat"];
        std::string eventName = bookedTicketData["event"];
        std::string note = bookedTicketData["note"];
        
        // Find the event by name
        Event* foundEvent = nullptr;
        for (const auto& event : theater.events) {
            if (event->getName() == eventName) {
                foundEvent = event;
                break;
            }
        }
        
        if (foundEvent) {
            theater.bookTicket(*foundEvent, row, seat, note);
        } else {
            // Ignore the ticket
        }
    }

    // Load purchased tickets
     for (const auto& purchasedTicketData : jsonData["purchasedTickets"]) {
        size_t row = purchasedTicketData["row"];
        size_t seat = purchasedTicketData["seat"];
        std::string eventName = purchasedTicketData["event"];
        std::string code = purchasedTicketData["code"];
        
        // Find the event by name
        Event* foundEvent = nullptr;
        for (const auto& event : theater.events) {
            if (event->getName() == eventName) {
                foundEvent = event;
                break;
            }
        }
        
        if (foundEvent) {
            theater.purchaseTicket(*foundEvent, row, seat);
            PurchasedTicket* purchasedTicket = theater.getPurchasedTicket(row, seat, *foundEvent); //something more optimized here 
            if (purchasedTicket) {
                purchasedTicket->setCode(code);
            }
        } else {
            // Ignore the ticket
        }
    }

    // Load free tickets
    for (const auto& freeTicketData : jsonData["freeTickets"]) {
        size_t row = freeTicketData["row"];
        size_t seat = freeTicketData["seat"];
        std::string eventName = freeTicketData["event"];        
        
        // Find the event by name
        Event* foundEvent = nullptr;
        for (const auto& event : theater.events) {
            if (event->getName() == eventName) {
                foundEvent = event;
                break;
            }
        }        
        
        if (foundEvent) {
            Ticket* ticket = new Ticket(row, seat, *foundEvent);
            theater.addFree(ticket);
        } else {
            // Ignore the ticket
        }
    }
}

