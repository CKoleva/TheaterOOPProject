/** @file Ticket.h
 *  @brief A class that represents a ticket for a specific event.
 *  
 *  @author Simona Koleva
 */


#pragma once
#include "Event.h"

using std::size_t;

/**
 * @class Ticket
 */
class Ticket {
protected:
    size_t row;  //!< Stores row of the ticket
    size_t seat;  //!< Stores the seat of the ticket
    Event event;  //!< Specifies the event

public:
    /**
    * @brief Constructs a Ticket object with the specified row, seat, and event.
    * @param row The row of the ticket.
    * @param seat The seat of the ticket.
    * @param event The event associated with the ticket.
    */
    Ticket(int row, int seat, const Event& event);

    /**
    * @brief Gets the row of the ticket.
    * @return The row of the ticket.
    */
    const size_t getRow() const;

    /**
    * @brief Gets the seat of the ticket.
    * @return The seat of the ticket.
    */
    const size_t getSeat() const;

    /**
    * @brief Gets the event associated with the ticket.
    * @return The event associated with the ticket.
    */
    const Event& getEvent() const;

    /**
    * @brief Prints the row and seat of the ticket.
    */
    virtual void printTicket() const;

    /*!
    * Creating a copy.
    * @note Virtual function.
    * @return A pointer to the cloned Ticket object.
    */
    virtual Ticket* clone();

    /**
    * @brief Virtual destructor.
    */
    virtual ~Ticket() = default;
};