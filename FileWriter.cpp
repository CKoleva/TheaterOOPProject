#include "FileWriter.h"

void FileWriter::saveTheaterData(Theater* theater, fstream& file) {
    json jsonData;

    jsonData["halls"] = convertHallsToJson(theater);
    jsonData["events"] = convertEventsToJson(theater);
    jsonData["bookedTickets"] = convertBookedTicketsToJson(theater);
    jsonData["purchasedTickets"] = convertPurchasedTicketsToJson(theater);

    writeJsonToFile(jsonData, file);
}

json FileWriter::convertHallsToJson(Theater* theater) {
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

json FileWriter::convertEventsToJson(Theater* theater) {
    json eventsData;

    for (const auto& event : theater->getEvents()) {
        json eventData;
        eventData["date"] = event->getDate().serialize();
        eventData["hallName"] = event->getHallName();
        eventData["eventName"] = event->getName();
        eventsData.push_back(std::move(eventData));
    }

    return eventsData;
}

json FileWriter::convertBookedTicketsToJson(Theater* theater) {
    json ticketsData;

    for (const auto& ticket : theater->getBookedTickets()) {
        json ticketData = convertTicketToJson(ticket);
        ticketData["note"] = ticket->getNote();
        ticketsData.push_back(std::move(ticketData));
    }

    return ticketsData;
}

json FileWriter::convertPurchasedTicketsToJson(Theater* theater) {
    json ticketsData;

    for (const auto& ticket : theater->getPurchasedTickets()) {
        json ticketData = convertTicketToJson(ticket);
        ticketsData.push_back(std::move(ticketData));
    }

    return ticketsData;
}

json FileWriter::convertTicketToJson(Ticket* ticket) {
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