/** @file Theater.h
 *  @brief A class theater represents a theater that manages halls, events, and tickets.
 *  
 *  @author Simona Koleva
 */

#pragma once
#include "Event.h"
#include "Ticket.h"
#include "Hall.h"
#include "BookedTicket.h"
#include "PurchasedTicket.h"


/** 
* @class Theater
*/
class Theater {
private:
    static Theater* instance;

    std::vector<Hall*> halls; //!< Vector of pointers to Hall objects
    std::vector<Event*> events; //!< Vector of pointers to Event objects
    std::vector<BookedTicket*> bookedTickets; //!< Vector of pointers to booked tickets
    std::vector<PurchasedTicket*> purchasedTickets; //!< Vector of pointers to purchased tickets
    std::vector<Ticket*> freeTickets; //!< Vector of pointers to free tickets

    /**
     * @brief Checks if a seat is available for a given event.
     * @param event The event to check.
     * @param row The row number of the seat.
     * @param seat The seat number in the row.
     * @return True if the seat is available, false otherwise.
     */
    bool isSeatAvailable(const Event& event, const size_t row, const size_t seat) const;

    /**
     * @brief Validates a unique code.
     * @param code The code to validate.
     * @return True if the code is valid, false otherwise.
     */
    bool validateUniqueCode(const string& code) const;

    /**
     * @brief Finds an event in the events vector.
     * @param eventName The name of the event.
     * @param date The date of the event.
     * @return A pointer to the found Event object, or nullptr if not found.
     */
    Event* findEvent(const string& eventName, const Date& date) const;

    /**
     * @brief Finds a hall by name.
     * @param name The name of the hall.
     * @return A pointer to the found Hall object, or nullptr if not found.
     */
    Hall* findHallByName(const std::string& name) const;

    /**
     * @brief Removes a ticket from the freeTickets vector.
     * @param event The event of the ticket.
     * @param row The row number of the ticket.
     * @param seat The seat number of the ticket.
     */
    void removeFreeTicket(const Event& event, size_t row, size_t seat);

    Theater();  //! Private default constructor
public:
    /**
     * @brief Gets the instance of the Theater (Singleton pattern).
     * @return The instance of the Theater.
     */
    static Theater* getInstance();

    /**
     * @brief Gets the vector of halls.
     * @return The vector of halls.
     */
    const std::vector<Hall*>& getHalls() const;

    /**
     * @brief Gets the vector of events.
     * @return The vector of events.
     */
    const std::vector<Event*>& getEvents() const;

    /**
     * @brief Gets the vector of booked tickets.
     * @return The vector of booked tickets.
     */
    const std::vector<BookedTicket*>& getBookedTickets() const;

    /**
     * @brief Gets the vector of free tickets.
     * @return The vector of free tickets.
     */
    const std::vector<Ticket*>& getFreeTickets() const;

    /**
     * @brief Gets the vector of purchased tickets.
     * @return The vector of purchased tickets.
     */
    const std::vector<PurchasedTicket*>& getPurchasedTickets() const;

    // FileReader-related methods

    /**
     * @brief Adds a hall to the theater.
     * @param hall The hall to add.
     */
    void addHall(Hall* hall);

    /**
     * @brief Adds a free ticket to the theater.
     * @param t The ticket to add.
     */
    void addFree(Ticket* t);

    // For Singleton design pattern
    Theater(const Theater&) = delete;
    Theater(Theater&&) = delete;
    Theater& operator=(const Theater&) = delete;
    Theater& operator=(Theater&&) = delete;

    /**
     * @brief Adds an event to the theater.
     * @param date The date of the event.
     * @param hallName The name of the hall.
     * @param eventName The name of the event.
     */
    void addEvent(const Date& date, const std::string& hallName, const std::string& eventName);

    // Ticket-related methods

    /**
     * @brief Books a ticket for a specific event.
     * @param row The row number of the ticket.
     * @param seat The seat number of the ticket.
     * @param date The date of the event.
     * @param eventName The name of the event.
     * @param note Additional note for the ticket.
     */
    void bookTicket(const size_t row, const size_t seat, const Date& date, const string& eventName, const string note);

    /**
     * @brief Purchases a ticket for a specific event.
     * @param row The row number of the ticket.
     * @param seat The seat number of the ticket.
     * @param date The date of the event.
     * @param eventName The name of the event.
     */
    void purchaseTicket(const size_t row, const size_t seat, const Date& date, const string& eventName);

    /**
     * @brief Unbooks a ticket for a specific event.
     * @param row The row number of the ticket.
     * @param seat The seat number of the ticket.
     * @param date The date of the event.
     * @param eventName The name of the event.
     */
    void unbookTicket(const size_t row, const size_t seat, const Date& date, const string& eventName);

    /**
     * @brief Checks the validity of a code.
     * @param code The code to check.
     */
    void check(const string& code) const;

    /**
     * @brief Displays the bookings for a specific date and event.
     * @param date The date of the event.
     * @param eventName The name of the event.
     */
    void displayBookings(const Date& date, const string& eventName) const;

    /**
     * @brief Displays the bookings for a specific date.
     * @param date The date of the event.
     */
    void displayBookings(const Date& date) const;

    /**
     * @brief Displays the bookings for a specific event.
     * @param eventName The name of the event.
     */
    void displayBookings(const string& eventName) const;

    /**
     * @brief Displays the available seats for a specific event and date.
     * @param eventName The name of the event.
     * @param date The date of the event.
     */
    void displayAvailableSeats(const string& eventName, const Date& date) const;

    /**
     * @brief Generates a report of bookings within a specific date range.
     * @param from The start date of the range.
     * @param to The end date of the range.
     */
    void report(const Date& from, const Date& to) const;

    /**
     * @brief Generates a report of bookings within a specific date range and hall.
     * @param from The start date of the range.
     * @param to The end date of the range.
     * @param hallName The name of the hall.
     */
    void report(const Date& from, const Date& to, const string& hallName) const;

    /**
     * @brief Generates a statistic of the most watched events.
     */
    void mostWatchedEventsStatistic() const;

    /**
     * @brief Friend function for FileReader to make all tickets free.
     * @param theater The Theater instance.
     */
    friend void makeAllTicketsFree(Theater* theater);

    /**
     * @brief Frees the memory allocated by the Theater instance.
     * @note This function is public because it will be handled by the Engine.
     */
    void free();

    static void deleteTheater();

    /**
     * @brief Default destructor.
     */
    ~Theater();

    /**
     * @brief Friend class declaration for FileReader.
     */
    friend class FileReader;
};