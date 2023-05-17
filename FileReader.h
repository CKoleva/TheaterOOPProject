#pragma once
#include <fstream>
#include <iostream>
#include "Theater.h"
#include "C:/Users/Laptop/Downloads/json.hpp"

class FileReader {
private:
   // Helper functions
   void loadHalls(Theater& theater, const nlohmann::json& jsonData);
   void loadEvents(Theater& theater, const nlohmann::json& jsonData);
   void loadBookedTickets(Theater& theater, const nlohmann::json& jsonData);
   void loadPurchasedTickets(Theater& theater, const nlohmann::json& jsonData);

public:
   // Main function for loading data
   static void loadTheaterData(Theater& theater, const std::string& filename);
};

