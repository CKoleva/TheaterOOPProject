#include "Ticket.h"
#include <random>
#include <sstream>

class PurchasedTicket : public Ticket {
private:
    string uniqueCode;

    string generateUniqueCode(size_t row, size_t seat);  //generates unique code

public:
    PurchasedTicket(size_t row, size_t seat, const Event& event); //parametric constructor

    PurchasedTicket* clone() override final;

    const string getUniqueCode() const; //getter for the unique code
};