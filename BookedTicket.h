/** @file BookedTicket.h
 *  @brief A class that represents a booked ticket for a specific event.
 *  
 *  @author Simona Koleva
 */

#include "Ticket.h"


/**
 * @class BookedTicket
 * @details Inherits from the Ticket class.
 */
class BookedTicket : public Ticket {
private:
    string note; //!< Stores the note associated with the booked ticket.

public:
    /**
     * @brief Parametric constructor for the BookedTicket class.
     * @param row The row of the ticket.
     * @param seat The seat of the ticket.
     * @param event The event associated with the ticket.
     * @param note The note associated with the booked ticket.
     */
    BookedTicket(int row, int seat, const Event& event, const string note); //parametric constructor

    /**
     * @brief Creates a clone of the BookedTicket object.
     * @note Virtual function override.
     * @return A pointer to the cloned BookedTicket object.
     */
    BookedTicket* clone() override final;

    /**
     * @brief Gets the note associated with the booked ticket.
     * @return The note.
     */
    const string& getNote() const;
};