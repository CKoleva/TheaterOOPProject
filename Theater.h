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

    bool isSeatAvailable(const Event& event, const size_t row, const size_t seat) const; //helper fuction to check availability
    bool validateUniqueCode(const string& code) const; //hepler function to check code
    Event* findEvent(const string& eventName, const Date& date) const;     //helper function to find Event in events vector
    Hall* findHallByName(const std::string& name) const;   //hepler function to find Hall
    void removeFreeTicket(const Event& event, size_t row, size_t seat); //hepler function to remove ticket from freeTickets vector

    Theater();  //private default constructor
public:
    static Theater* getInstance(); // Static function to get the instance of Theater

    // Getters
    const std::vector<Hall*>& getHalls() const;
    const std::vector<Event*>& getEvents() const;
    const std::vector<BookedTicket*>& getBookedTickets() const;
    const std::vector<Ticket*>& getFreeTickets() const;
    const std::vector<PurchasedTicket*>& getPurchasedTickets() const;

    // FileReader-related methods
    void addHall(Hall* hall);
    void addFree(Ticket* t);

    // For Singleton design pattern
    Theater(const Theater&) = delete;
    Theater(Theater&&) = delete;
    Theater& operator=(const Theater&) = delete;
    Theater& operator=(Theater&&) = delete;

    // Event-related methods
    void addEvent(const Date& date, const std::string& hallName, const std::string& eventName);

    // Ticket-related methods
    void bookTicket(const size_t row, const size_t seat, const Date& date, const string& eventName, const string note);
    void purchaseTicket(const size_t row, const size_t seat, const Date& date, const string& eventName);
    void unbookTicket(const size_t row, const size_t seat, const Date& date, const string& eventName);
    void check(const string& code) const;
    void displayBookings(const Date& date, const string& eventName) const;
    void displayBookings(const Date& date) const;
    void displayBookings(const string& eventName) const;
    void displayAvailableSeats(const string& eventName, const Date& date) const;
    void report(const Date& from, const Date& to) const;
    void report(const Date& from, const Date& to, const string& hallName) const;
    void mostWatchedEventsStatistic() const;

    //friend function for FileReader
    friend void makeAllTicketsFree(Theater* theater);

    void free(); //deallocate memory public because it will be handled by Engine
    ~Theater();

    friend class FileReader;
};