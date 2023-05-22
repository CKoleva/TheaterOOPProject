#include "Theater.h"
#include <iomanip>
#include <fstream>
#include "C:/Users/Laptop/Downloads/nlohmann.json/json.hpp"

using nlohmann::json;
using std::fstream;

class FileWriter {
private:
    // Helper functions
    static json convertHallsToJson(const Theater* theater);
    static json convertEventsToJson(const Theater* theater);
    static json convertBookedTicketsToJson(const Theater* theater);
    static json convertPurchasedTicketsToJson(const Theater* theater);
    static json convertTicketToJson(const Ticket* ticket);

    static void writeJsonToFile(const json& jsonData, fstream& file);

public:
    // Main function for saving data to file
    static void saveTheaterData(const Theater* theater, fstream& file);
};