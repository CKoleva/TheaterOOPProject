/** @file Date.h
* @brief A class that represents a date by the ISO 8601 standard
*
* @author Simona Koleva
*/

#pragma once
#include "ISerializable.h"
#include <cstddef>

using std::size_t;

/**
 * @class Date
 * @details Implements the ISerializable interface.
 */
class Date : public ISerializable {
private:
    int year;   //!< Stores the year value.
    int month;  //!< Stores the month value.
    int day;    //!< Stores the day value.

    /**
     * @brief Checks if the date is valid.
     * @return True if the date is valid, false otherwise.
     */
    bool isValidDate() const;

public:
    /**
     * @brief Parametric constructor for the Date class.
     * @param day The day value.
     * @param month The month value.
     * @param year The year value.
     */
    Date(size_t year, size_t month, size_t day);

    /**
     * @brief Constructor for the Date class that accepts a string representation of the date.
     * @param dateStr The string representation of the date (in the format "dd/mm/yyyy").
     */
    Date(const string dateStr);

    // Getters

    /**
     * @brief Gets the year value of the date.
     * @return The year value.
     */
    int getYear() const;
    
    /**
     * @brief Gets the month value of the date.
     * @return The month value.
     */
    int getMonth() const;

    /**
     * @brief Gets the day value of the date.
     * @return The day value.
     */
    int getDay() const;

    // Comparison methods

    /**
     * @brief Overloaded equality operator for comparing Date objects.
     * @param other The other Date object to compare with.
     * @return True if the dates are equal, false otherwise.
     */
    bool operator==(const Date& other) const;

    /**
     * @brief Overloaded inequality operator for comparing Date objects.
     * @param other The other Date object to compare with.
     * @return True if the dates are not equal, false otherwise.
     */
    bool operator!=(const Date& other) const;

    /**
     * @brief Overloaded less than operator for comparing Date objects.
     * @param other The other Date object to compare with.
     * @return True if this date is less than the other date, false otherwise.
     */
    bool operator<(const Date& other) const;

    /**
     * @brief Overloaded less than or equal to operator for comparing Date objects.
     * @param other The other Date object to compare with.
     * @return True if this date is less than or equal to the other date, false otherwise.
     */
    bool operator<=(const Date& other) const;

    /**
     * @brief Overloaded greater than operator for comparing Date objects.
     * @param other The other Date object to compare with.
     * @return True if this date is greater than the other date, false otherwise.
     */
    bool operator>(const Date& other) const;

    /**
     * @brief Overloaded greater than or equal to operator for comparing Date objects.
     * @param other The other Date object to compare with.
     * @return True if this date is greater than or equal to the other date, false otherwise.
     */
    bool operator>=(const Date& other) const;

    /**
     * @brief Serializes the Date object to a string representation.
     * @note Implements the serialize() function from the ISerializable interface.
     * @return The serialized string representation of the Date object.
     */
    const string serialize() const override final;

    /**
     * @brief Deserializes a string representation and sets the state of the Date object.
     * @note Implements the deserialize() function from the ISerializable interface.
     * @param data The string representation to deserialize.
     */
    void deserialize(const string& data) override final;
};