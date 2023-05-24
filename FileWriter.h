#include "Theater.h"
#include <iomanip>
#include <fstream>
#include "C:/Users/Laptop/Downloads/nlohmann.json/json.hpp"

using nlohmann::json;
using std::fstream;

class FileWriter {
private:
    // Helper functions
    static json convertHallsToJson(Theater* theater);
    static json convertEventsToJson(Theater* theater);
    static json convertBookedTicketsToJson(Theater* theater);
    static json convertPurchasedTicketsToJson(Theater* theater);
    static json convertTicketToJson(Ticket* ticket);

    static void writeJsonToFile(const json& jsonData, fstream& file);

public:
    // Main function for saving data to file
    static void saveTheaterData(Theater* theater, fstream& file);
};