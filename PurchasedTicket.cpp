#include "PurchasedTicket.h"
#include <iomanip>

std::string PurchasedTicket::generateUniqueCode(size_t row, size_t seat) {
    // Generate a random number for the unique identifier           !!Used code!!
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1000, 9999);
    int uniqueId = dis(gen);                                        // .. up to here

    // Combine the seat, row, and unique identifier to create the code
    std::ostringstream oss;
    oss << "TR" << std::setw(3) << std::setfill('0') << row << "S"
    << std::setw(3) << std::setfill('0') << seat << "D" << uniqueId;
    
    return oss.str();
}

PurchasedTicket* PurchasedTicket::clone() {
    return new PurchasedTicket(*this);
}

PurchasedTicket::PurchasedTicket(size_t row, size_t seat, const Event& event)
    : Ticket(row, seat, event) {
    this->uniqueCode = generateUniqueCode(row, seat);
}

const string PurchasedTicket::getUniqueCode() const {
    return this->uniqueCode;
}