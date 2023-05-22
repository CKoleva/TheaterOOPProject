#include "FileWriter.h"

void FileWriter::saveTheaterData(const Theater* theater, fstream& file) {
    json jsonData;

    jsonData["halls"] = convertHallsToJson(theater);
    jsonData["events"] = convertEventsToJson(theater);
    jsonData["bookedTickets"] = convertBookedTicketsToJson(theater);
    jsonData["purchasedTickets"] = convertPurchasedTicketsToJson(theater);

    writeJsonToFile(jsonData, file);
}

json FileWriter::convertHallsToJson(const Theater* theater) {
    json hallsData;

    for (const auto& hall : theater->getHalls()) {
        json hallData;
        hallData["name"] = hall->getName();
        hallData["numRows"] = hall->getNumberOfRows();
        hallData["numSeats"] = hall->getNumberOfSeats();
        hallsData.push_back(hallData);
    }

    return hallsData;
}

json FileWriter::convertEventsToJson(const Theater* theater) {
    json eventsData;

    for (const auto& event : theater->getEvents()) {
        json eventData;
        eventData["date"] = event->getDate().serialize();
        eventData["hallName"] = event->getHallName();
        eventData["eventName"] = event->getName();
        eventsData.push_back(eventData);
    }

    return eventsData;
}

json FileWriter::convertBookedTicketsToJson(const Theater* theater) {
    json ticketsData;

    for (const auto& ticket : theater->getBookedTickets()) {
        json ticketData = convertTicketToJson(ticket);
        ticketData.push_back(ticket->getNote());
        ticketsData.push_back(ticketData);
    }

    return ticketsData;
}

json FileWriter::convertPurchasedTicketsToJson(const Theater* theater) {
    json ticketsData;

    for (const auto& ticket : theater->getPurchasedTickets()) {
        json ticketData = convertTicketToJson(ticket);
        ticketsData.push_back(ticketData);
    }

    return ticketsData;
}

json FileWriter::convertTicketToJson(const Ticket* ticket) {
    json ticketData;
    ticketData["row"] = ticket->getRow();
    ticketData["seat"] = ticket->getSeat();
    ticketData["eventName"] = ticket->getEvent().getName();
    ticketData["date"] = ticket->getEvent().getDate().serialize();
    return ticketData;
}

void FileWriter::writeJsonToFile(const json& jsonData, fstream& file) {
    file << std::setw(4) << jsonData << std::endl;
}