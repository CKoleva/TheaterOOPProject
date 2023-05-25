/** 
 * @file FileReader.h
 * @brief Contains the declaration of the FileReader class, which is responsible for reading theater data from a file and populating the Theater
 * @note The FileReader class assumes that the file format follows a specific JSON structure for theater data.
 * Any deviations from the expected structure may result in parsing errors or incorrect data loading.
 * 
 * @author Simona Koleva
 */

#pragma once
#include <fstream>
#include <iostream>
#include "Theater.h"
#include "C:/Users/Laptop/Downloads/nlohmann.json/json.hpp"

using nlohmann::json;

/**
 * @class FileReader
 */
class FileReader {
private:
   /**
     * @brief Helper function to load hall information from JSON data.
     * @param theater Pointer to the Theater instance.
     * @param jsonData The JSON data containing hall information.
     */
   static void loadHalls(Theater* theater, json& jsonData);

   /**
     * @brief Helper function to load event information from JSON data.
     * @param theater Pointer to the Theater instance.
     * @param jsonData The JSON data containing event information.
     */
   static void loadEvents(Theater* theater, json& jsonData);

   /**
     * @brief Helper function to load booked ticket information from JSON data.
     * @param theater Pointer to the Theater instance.
     * @param jsonData The JSON data containing booked ticket information.
     */
   static void loadBookedTickets(Theater* theater, json& jsonData);

   /**
     * @brief Helper function to load purchased ticket information from JSON data.
     * @param theater Pointer to the Theater instance.
     * @param jsonData The JSON data containing purchased ticket information.
     */
   static void loadPurchasedTickets(Theater* theater, json& jsonData);

public:
    /**
     * @brief Loads theater data from a file into a Theater instance.
     * @param theater Pointer to the Theater instance.
     * @param file The file stream to read the data from.
     */
   static void loadTheaterData(Theater* theater, std::fstream& file);
};

