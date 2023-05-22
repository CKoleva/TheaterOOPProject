#pragma once
#include <fstream>
#include <iostream>
#include "Theater.h"
#include "C:/Users/Laptop/Downloads/nlohmann.json/json.hpp"

using nlohmann::json;

class FileReader {
private:
   // Helper functions
   static void loadHalls(Theater* theater, json& jsonData);
   static void loadEvents(Theater* theater, json& jsonData);
   static void loadBookedTickets(Theater* theater, json& jsonData);
   static void loadPurchasedTickets(Theater* theater, json& jsonData);

public:
   // Main function for loading data
   static void loadTheaterData(Theater* theater, std::fstream& file);      //make it use Theater*
};

