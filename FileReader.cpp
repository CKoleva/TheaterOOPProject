#include "FileReader.h"

void FileReader::loadHalls(Theater& theater, const nlohmann::json& jsonData) {
    for (const auto& hallData : jsonData["halls"]) {
        std::string name = hallData["name"];
        size_t numRows = hallData["numRows"];
        size_t numSeats = hallData["numSeats"];
        Hall* hall = new Hall(name, numRows, numSeats);
        theater.addHall(hall);
    }
}

void FileReader::loadEvents(Theater& theater, const nlohmann::json& jsonData) {
    for (const auto& eventData : jsonData["events"]) {
        Date date(eventData["date"]);
        std::string hallName = eventData["hallName"];
        std::string eventName = eventData["eventName"];
        theater.addEvent(date, hallName, eventName);
    }
}

void FileReader::loadBookedTickets(Theater& theater, const nlohmann::json& jsonData) {
    for (const auto& bookedTicketData : jsonData["bookedTickets"]) {
        size_t row = bookedTicketData["row"];
        size_t seat = bookedTicketData["seat"];
        std::string note = bookedTicketData["note"];
        std::string eventName = bookedTicketData["eventName"];
        std::string hallName = bookedTicketData["hallName"];
        Date date(bookedTicketData["date"]);
        
        Event event(eventName, date, hallName);
        Event* found = theater.findEvent(event);
        
        if (found != nullptr) {
            theater.bookTicket(event, row, seat, note);
        } else {
            // Ignore the ticket
        }
    }
}

void FileReader::loadPurchasedTickets(Theater& theater, const nlohmann::json& jsonData) {
    for (const auto& purchasedTicketData : jsonData["purchasedTickets"]) {
        size_t row = purchasedTicketData["row"];
        size_t seat = purchasedTicketData["seat"];
        std::string eventName = purchasedTicketData["eventName"];
        std::string hallName = purchasedTicketData["hallName"];
        Date date = purchasedTicketData["date"];
        
        Event event(eventName, date, hallName);
        Event* found = theater.findEvent(event);

        if (found != nullptr) {
            theater.purchaseTicket(event, row, seat);
        } else {
            // Ignore the ticket
        }
    }
}

void FileReader::loadTheaterData(Theater& theater, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open the file: " + filename);
    }
    nlohmann::json jsonData;
    file >> jsonData;
    file.close();

    loadHalls(theater, jsonData);
    loadEvents(theater, jsonData);

    makeAllTicketsFree(theater);

    loadBookedTickets(theater, jsonData);
    loadPurchasedTickets(theater, jsonData);
}