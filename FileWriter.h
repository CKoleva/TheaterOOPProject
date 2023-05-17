#include "Theater.h"
#include <iomanip>
#include "C:/Users/Laptop/Downloads/json.hpp"

using nlohmann::json;

class FileWriter {
public:
    static void saveTheaterData(const Theater& theater, const string& filename);

private:
    static json convertHallsToJson(const Theater& theater);
    static json convertEventsToJson(const Theater& theater);
    static json convertBookedTicketsToJson(const Theater& theater);
    static json convertPurchasedTicketsToJson(const Theater& theater);
    static json convertTicketToJson(const Ticket& ticket);

    static void writeJsonToFile(const nlohmann::json& jsonData, const string& filename);
};