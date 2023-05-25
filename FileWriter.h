/** 
 * @file FileWriter.h
 * @brief Contains the declaration of the FileWriter class, which is responsible for converting theater data from a Theater instance to JSON format
 * and writing it to a file. It uses the nlohmann::json library for JSON serialization.
 *
 * @author Simona Koleva
 */

#include "Theater.h"
#include <iomanip>
#include <fstream>
#include "C:/Users/Laptop/Downloads/nlohmann.json/json.hpp"

using nlohmann::json;
using std::fstream;

/**
* @class FileWriter
*/
class FileWriter {
private:
    /**
     * @brief Helper function to convert hall information from Theater instance to JSON.
     * @param theater Pointer to the Theater instance.
     * @return The JSON data representing hall information.
     */
    static json convertHallsToJson(Theater* theater);

    /**
     * @brief Helper function to convert event information from Theater instance to JSON.
     * @param theater Pointer to the Theater instance.
     * @return The JSON data representing event information.
     */
    static json convertEventsToJson(Theater* theater);

    /**
     * @brief Helper function to convert booked ticket information from Theater instance to JSON.
     * @param theater Pointer to the Theater instance.
     * @return The JSON data representing booked ticket information.
     */
    static json convertBookedTicketsToJson(Theater* theater);

    /**
     * @brief Helper function to convert purchased ticket information from Theater instance to JSON.
     * @param theater Pointer to the Theater instance.
     * @return The JSON data representing purchased ticket information.
     */
    static json convertPurchasedTicketsToJson(Theater* theater);

    /**
     * @brief Helper function to convert ticket information to JSON.
     * @param ticket Pointer to the Ticket instance.
     * @return The JSON data representing the ticket information.
     */
    static json convertTicketToJson(Ticket* ticket);

    /**
     * @brief Writes JSON data to a file.
     * @param jsonData The JSON data to write.
     * @param file The file stream to write the data to.
     */
    static void writeJsonToFile(const json& jsonData, fstream& file);

public:
   /**
    * @brief Saves theater data from a Theater instance to a file.
    * @param theater Pointer to the Theater instance.
    * @param file The file stream to write the data to.
    */
    static void saveTheaterData(Theater* theater, fstream& file);
};