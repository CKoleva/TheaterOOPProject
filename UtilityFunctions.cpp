#include "Theater.h"

void makeAllTicketsFree(Theater* theater) {
    std::vector<Event*> events =  theater->getEvents();
    for (const Event* event : events)
    {
        Hall* hall = theater->findHallByName(event->getHallName());
        size_t rows = hall->getNumberOfRows();
        size_t seats = hall->getNumberOfSeats();
        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < seats; j++)
            {
                theater->addFree(new Ticket(i, j, *event));
            }
        }   
    }
}