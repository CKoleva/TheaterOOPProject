/** @file PurchasedTicket.h
 *  @brief A class theater represents a purchased ticket.
 *  
 *  @author Simona Koleva
 */

#include "Ticket.h"
#include <random>
#include <sstream>

class PurchasedTicket : public Ticket {
private:
    string uniqueCode; //! Stres the code of the ticket

    /**
     * @brief Generates a unique code based on the row and seat numbers.
     * @param row The row number of the ticket.
     * @param seat The seat number of the ticket.
     * @return The generated unique code.
     */
    string generateUniqueCode(size_t row, size_t seat);

public:
    /**
     * @brief Constructs a PurchasedTicket object.
     * @param row The row number of the ticket.
     * @param seat The seat number of the ticket.
     * @param event The event for which the ticket is purchased.
     */
    PurchasedTicket(size_t row, size_t seat, const Event& event);

    /**
     * @brief Creates a clone of the PurchasedTicket object.
     * @note Virtual function override.
     * @return A pointer to the cloned PurchasedTicket object.
     */
    PurchasedTicket* clone() override final;

    /**
     * @brief Gets the unique code of the ticket.
     * @return The unique code.
     */
    const string getUniqueCode() const; //getter for the unique code
};