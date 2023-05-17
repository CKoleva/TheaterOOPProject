#include "FileWriter.h"
#include <fstream>

class FileWriter {
public:
    static void saveTheaterData(const Theater& theater, const string& filename);
 
private:
    static json convertHallsToJson(const Theater& theater);
    static json convertEventsToJson(const Theater& theater);
    static json convertBookedTicketsToJson(const Theater& theater);
    static json convertPurchasedTicketsToJson(const Theater& theater);
    static json convertTicketToJson(const Ticket& ticket);

    static void writeJsonToFile(const json& jsonData, const string& filename);
};

void FileWriter::saveTheaterData(const Theater& theater, const string& filename) {
    json jsonData;

    jsonData["halls"] = convertHallsToJson(theater);
    jsonData["events"] = convertEventsToJson(theater);
    jsonData["bookedTickets"] = convertBookedTicketsToJson(theater);
    jsonData["purchasedTickets"] = convertPurchasedTicketsToJson(theater);

    writeJsonToFile(jsonData, filename);
}

json FileWriter::convertHallsToJson(const Theater& theater) {
    json hallsData;

    for (const auto& hall : theater.getHalls()) {
        json hallData;
        hallData["name"] = hall->getName();
        hallData["numRows"] = hall->getNumberOfRows();
        hallData["numSeats"] = hall->getNumberOfSeats();
        hallsData.push_back(hallData);
    }

    return hallsData;
}

json FileWriter::convertEventsToJson(const Theater& theater) {
    json eventsData;

    for (const auto& event : theater.getEvents()) {
        json eventData;
        eventData["date"] = event->getDate().serialize();
        eventData["hallName"] = event->getHallName();
        eventData["eventName"] = event->getName();
        eventsData.push_back(eventData);
    }

    return eventsData;
}

json FileWriter::convertBookedTicketsToJson(const Theater& theater) {
    json ticketsData;

    for (const auto& ticket : theater.getBookedTickets()) {
        nlohmann::json ticketData = convertTicketToJson(*ticket);
        ticketsData.push_back(ticketData);
    }

    return ticketsData;
}

json FileWriter::convertPurchasedTicketsToJson(const Theater& theater) {
    json ticketsData;

    for (const auto& ticket : theater.getPurchasedTickets()) {
        json ticketData = convertTicketToJson(*ticket);
        ticketsData.push_back(ticketData);
    }

    return ticketsData;
}

json FileWriter::convertTicketToJson(const Ticket& ticket) {
    json ticketData;
    ticketData["row"] = ticket.getRow();
    ticketData["seat"] = ticket.getSeat();
    ticketData["eventName"] = ticket.getEvent().getName();
    ticketData["hallName"] = ticket.getEvent().getHallName();
    ticketData["date"] = ticket.getEvent().getDate().serialize();
    return ticketData;
}

void FileWriter::writeJsonToFile(const json& jsonData, const string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open the file: " + filename);
    }
    file << std::setw(4) << jsonData << std::endl;
    file.close();
}