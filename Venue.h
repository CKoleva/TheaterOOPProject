/** @file Venue.h
 *  @brief A class that represents a venue or a location where events can take place.
 *  @note Abstract base class that provides a common interface for specific types of venues.
 * 
 *  @author Simona Koleva
 */

#pragma once
#include <string>
#include <cstddef>

using std::string;
using std::size_t;

class Venue {
protected:
    string name; //!< Stores the name of the venue.
public:
    /**
    * @brief Constructs a Venue object with the specified name.
    * @param name The name of the venue.
    */
    Venue(const string& name);

    /**
    * @brief Gets the name associated with the venue.
    * @return The name of the venue.
    */
    const string& getName() const;
    
    virtual ~Venue() = default;
};