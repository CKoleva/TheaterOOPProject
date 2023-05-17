#pragma once
#include "Event.h"
#include "Ticket.h"
#include "Hall.h"
#include "BookedTicket.h"
#include "PurchasedTicket.h"

class Theater {
private:
    static Theater* instance;

    std::vector<Hall*> halls; //vector of pointers to Hall objects
    std::vector<Event*> events; //vector of pointers to Event objects
    std::vector<BookedTicket*> bookedTickets; //vector of pointers to booked tickets
    std::vector<PurchasedTicket*> purchasedTickets; //vector of pointers to purchased tickets
    std::vector<Ticket*> freeTickets; //vector of pointers to free tickets

    void free(); //deallocate memory
    bool isSeatAvailable(const Event& event, size_t row, size_t seat) const; //helper fuction to check availability
    bool validateUniqueCode(const string& code) const; //hepler function to check code
    Event* findEvent(const Event& event) const;
    Hall* Theater::findHallByName(const std::string& name) const;

    Theater();  //private default constructor
public:
    static Theater* getInstance(); //static function to get the instance of Theater

    void addHall(Hall* hall);
    Event& getEvent(const size_t idx) const;
    void addFree(Ticket* t);

    //for Singleton design pattern
    Theater(const Theater&) = delete;
    Theater(Theater&&) = delete;
    Theater& operator=(const Theater&) = delete;
    Theater& operator=(Theater&&) = delete;

    // Event-related methods
    void addEvent(const Date& date, const std::string& hallName, const std::string& eventName);

    // Ticket-related methods
    bool bookTicket(const Event& event, size_t row, size_t seat, const string note);
    bool purchaseTicket(const Event& event, size_t row, size_t seat);
    bool unbookTicket(const Event& event, size_t row, size_t seat);
    void check(const string& code) const;
    void displayBookings(const Event& event,const Date& date);
    void displayBookings(const Date& date);
    void displayAvailableSeats(const Event& event, const Date& date);

    ~Theater();

    friend class FileReader;
};