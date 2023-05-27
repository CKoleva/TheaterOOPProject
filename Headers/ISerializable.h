/** @file ISerializable.h
 * 
 *  @author Simona Koleva
 */

#pragma once
#include <string>
#include <sstream>

using std::stringstream;
using std::string;

/**
 * @interface ISerializable
 * @brief Interface for objects that can be serialized and deserialized.
 */
class ISerializable {
public:
    /**
     * @brief Serializes the object into a string representation.
     * @return The serialized string.
     */
    virtual const string serialize() const = 0;

    /**
     * @brief Deserializes the object from a string representation.
     * @param data The serialized string data.
     */
    virtual void deserialize(const string& data) = 0;
};