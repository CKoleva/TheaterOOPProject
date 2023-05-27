#include "../Headers/FileReader.h"

void FileReader::loadHalls(Theater* theater, json& jsonData) {
    for (auto& hallData : jsonData["halls"]) {
        string name = hallData["name"];
        size_t numRows = hallData["numRows"];
        size_t numSeats = hallData["numSeats"];
        Hall* hall = new Hall(name, numRows, numSeats);
        theater->addHall(hall);
    }
}

void FileReader::loadEvents(Theater* theater, json& jsonData) {
    for (const auto& eventData : jsonData["events"]) {
        Date date(eventData["date"]);
        string hallName = eventData["hallName"];
        string eventName = eventData["eventName"];
        theater->addEvent(date, hallName, eventName);
    }
}

void FileReader::loadBookedTickets(Theater* theater, json& jsonData) {
    for (const auto& bookedTicketData : jsonData["bookedTickets"]) {
        size_t row = bookedTicketData["row"];
        size_t seat = bookedTicketData["seat"];
        string eventName = bookedTicketData["eventName"];
        Date date(bookedTicketData["date"]);
        string note = bookedTicketData["note"];
        
        theater->bookTicket(row, seat, date, eventName, note);
    }
}

void FileReader::loadPurchasedTickets(Theater* theater, json& jsonData) {
    for (const auto& purchasedTicketData : jsonData["purchasedTickets"]) {
        size_t row = purchasedTicketData["row"];
        size_t seat = purchasedTicketData["seat"];
        string eventName = purchasedTicketData["eventName"];
        Date date(purchasedTicketData["date"]);
        
        theater->purchaseTicket(row, seat, date, eventName);
    }
}

void FileReader::loadTheaterData(Theater* theater, std::fstream& file) {
    json jsonData;
    file >> jsonData;
    
    if (jsonData.contains("halls")) {
        loadHalls(theater, jsonData);
    }

    if (jsonData.contains("events")) {
        loadEvents(theater, jsonData);
        makeAllTicketsFree(theater);
    }

    if (jsonData.contains("bookedTickets")) {
        loadBookedTickets(theater, jsonData);
    }

    if (jsonData.contains("purchasedTickets")) {
        loadPurchasedTickets(theater, jsonData);
    }
}