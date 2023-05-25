/** @file Event.h
* @brief A class that represents an event held at a venue.
*
* @author Simona Koleva
*/
#pragma once
#include"Venue.h"
#include "Date.h"


/**
 * @class Event
 * @details Inherits from the Venue class.
 */
class Event : public Venue {
private:
    Date date;  //!< Stores the date of the event.
    string hallName;  //!< Stores the name of the hall where the event takes place.
    size_t purchasedTickets;  //!< Stores the count of purchased tickets for the event.

public:
    /**
     * @brief Parametric constructor for the Event class.
     * @param name The name of the event.
     * @param date The date of the event.
     * @param hallName The name of the hall where the event takes place.
     */
    Event(const string& name, const Date& date, const string& hallName);

    // Getters

    /**
     * @brief Gets the name of the event.
     * @return The event name.
     */
    const string& getName() const;

    /**
     * @brief Gets the date of the event.
     * @return The event date.
     */
    const Date& getDate() const;

    /**
     * @brief Gets the name of the hall where the event takes place.
     * @return The hall name.
     */
    const string& getHallName() const;

    /**
     * @brief Gets the count of purchased tickets for the event.
     * @return The count of purchased tickets.
     */
    const size_t getPurchasedTicketsCount() const;

    /**
     * @brief Overloaded equality operator for comparing Event objects.
     * @param other The other Event object to compare with.
     * @return True if the events are equal, false otherwise.
     */
    bool operator==(const Event& other) const;

    /**
     * @brief Increases the count of purchased tickets by one.
     */
    void increasePTCount();

    /**
     * @brief Creates a clone of the Event object.
     * @note Virtual function override.
     * @return A pointer to the cloned Event object.
     */
    Event* clone();
};