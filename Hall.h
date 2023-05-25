/** @file Hall.h
 *  @brief A class that represents a hall in a theater.
 *  
 *  @author Simona Koleva
 */

#pragma once
#include "Venue.h"


/**
 * @class Hall
 * @details Inherits from the Venue class.
 */
class Hall : public Venue {
private:
    size_t numberOfRows; //!< Stores the number of rows in the hall
    size_t numberOfSeats; //!< Stores the number of seats in each row

public: 
    /**
     * @brief Parametric constructor for the Hall class.
     * @param name The name of the hall.
     * @param rows The number of rows in the hall.
     * @param seats The number of seats in each row.
     */
    Hall(const string name, const size_t rows, const size_t seats);

    // Getters

    /**
     * @brief Gets the number of rows in the hall.
     * @return The number of rows.
     */
    const size_t getNumberOfRows() const;

    /**
     * @brief Gets the number of seats in each row of the hall.
     * @return The number of seats.
     */
    const size_t getNumberOfSeats() const;

    /**
     * @brief Creates a clone of the Hall object.
     * @note Virtual function override.
     * @return A pointer to the cloned Hall object.
     */
    Hall* clone();
};
