#define DOCTEST_CONFIG_IMPLEMENT
#include "../doctest.h"
#include "../Headers/Engine.h"

TEST_CASE("BookedTicket constructor and getters") {
    Event event("EventName", Date(2023, 5, 17), "HallName");
    BookedTicket ticket(2, 5, event, "Note");

    CHECK(ticket.getRow() == 2);
        (ticket.getSeat() == 5);
    CHECK(ticket.getEvent() == event);
    CHECK(ticket.getNote() == "Note");
}

TEST_CASE("BookedTicket - Clone") {
    Event event("EventName", Date(2023, 5, 17), "HallName");
    BookedTicket ticket(2, 5, event, "Note");

    BookedTicket* clonedTicket = ticket.clone();
    CHECK(clonedTicket != nullptr);
    CHECK(clonedTicket->getEvent() == ticket.getEvent());
    CHECK(clonedTicket->getNote() == ticket.getNote());
    CHECK(clonedTicket->getRow() == ticket.getRow());
    CHECK(clonedTicket->getSeat() == ticket.getSeat());

    delete clonedTicket;
}

TEST_CASE("CommandLine - Valid Command Line") {
    CommandLine cmd("   command arg1 \"arg2 with space\"  arg3  ");
    CHECK(cmd.getSize() == 4);

    std::vector<std::string> expectedArgs{"COMMAND", "arg1", "arg2 with space", "arg3"};
    CHECK(cmd.getArgv() == expectedArgs);
}

TEST_CASE("CommandLine - Empty Command") {
    CHECK_THROWS_AS(CommandLine(""), std::invalid_argument);
}

TEST_CASE("CommandLine - Invalid Quotes Count") {
    CHECK_THROWS_AS(CommandLine("command \"arg1"), std::invalid_argument);
    CHECK_THROWS_AS(CommandLine("command arg1\""), std::invalid_argument);
}

TEST_CASE("Date serialization and deserialization") {
    Date date(2023, 5, 17);
    std::string serializedDate = date.serialize();

    Date deserializedDate(serializedDate);

    CHECK(deserializedDate == date);
}

TEST_CASE("Date comparison operators") {
    Date date1(2023, 5, 17);
    Date date2(2023, 5, 17);
    Date date3(2023, 5, 18);
    Date date4(2023, 6, 17);
    Date date5(2024, 5, 17);

    SUBCASE("Equality") {
        CHECK(date1 == date2);
    }

    SUBCASE("Inequality") {
        CHECK(date2 != date3);
        CHECK(date2 != date4);
        CHECK(date2 != date5);
    }

    SUBCASE("Greater than") {
        CHECK(date4 > date1);
        CHECK(date5 > date1);
        CHECK(date3 > date1);
    }


    SUBCASE("Greater than or equal") {
        CHECK(date1 >= date2);
        CHECK(date3 >= date1);
        CHECK(date4 >= date1);
        CHECK(date5 >= date1);
    }

    SUBCASE("Less than") {
        CHECK(date1 < date3);
        CHECK(date1 < date4);
        CHECK(date1 < date5);
    }

    SUBCASE("Less than or equal") {
        CHECK(date1 <= date2);
        CHECK(date1 <= date3);
        CHECK(date1 <= date4);
        CHECK(date1 <= date5);
    }
}

TEST_CASE("Date invalid date string throws exception") {
    CHECK_THROWS_AS(Date("2023-13-01"), std::runtime_error);
    CHECK_THROWS_AS(Date("2023-02-30"), std::runtime_error);
    CHECK_THROWS_AS(Date("2023-04-31"), std::runtime_error);
    CHECK_THROWS_AS(Date("2023-06-31"), std::runtime_error);
    CHECK_THROWS_AS(Date("2023-11-31"), std::runtime_error);
}

TEST_CASE("Date valid date string does not throw exception") {
    CHECK_NOTHROW(Date("2023-01-01"));
    CHECK_NOTHROW(Date("2023-02-28"));
    CHECK_NOTHROW(Date("2023-03-31"));
    CHECK_NOTHROW(Date("2023-07-31"));
    CHECK_NOTHROW(Date("2023-08-31"));
}

TEST_CASE("Event constructor") {
    SUBCASE("Constructing an Event") {
        Date date(10, 5, 2023);
        Event event("Concert", date, "Hall A");

        CHECK(event.getName() == "Concert");
        CHECK(event.getDate() == date);
        CHECK(event.getHallName() == "Hall A");
        CHECK(event.getPurchasedTicketsCount() == 0);
    }
}

TEST_CASE("Event - Equality operator") {
    SUBCASE("Comparing equal events") {
        Date date(10, 5, 2023);
        Event event1("Concert", date, "Hall B");
        Event event2("Concert", date, "Hall B");

        CHECK(event1 == event2);
    }

    SUBCASE("Comparing different events") {
        Date date1(10, 5, 2023);
        Date date2(11, 5, 2023);
        Event event1("Concert", date1, "Hall A");
        Event event2("Festival", date1, "Hall A");
        Event event3("Concert", date2, "Hall A");

        CHECK_FALSE(event1 == event2);
        CHECK_FALSE(event1 == event3);
    }
}

TEST_CASE("Event - increasePTCount") {
    SUBCASE("Incrementing purchased tickets' count") {
        Date date(10, 5, 2023);
        Event event("Concert", date, "Hall A");

        event.increasePTCount();

        CHECK(event.getPurchasedTicketsCount() == 1);
    }
}

TEST_CASE("Event - Clone") {
    SUBCASE("Cloning an Event") {
        Date date(10, 5, 2023);
        Event event("Concert", date, "Hall A");

        Event* clonedEvent = event.clone();

        CHECK(*clonedEvent == event);

        delete clonedEvent;
    }
}

TEST_CASE("Hall constructor and getters") {
    Hall hall("HallName", 5, 10);

    CHECK(hall.getName() == "HallName");
    CHECK(hall.getNumberOfRows() == 5);
    CHECK(hall.getNumberOfSeats() == 10);
}

TEST_CASE("Hall - Clone") {
    Hall originalHall("HallName", 5, 10);
    Hall* clonedHall = originalHall.clone();

    CHECK(clonedHall != nullptr);
    CHECK(originalHall.getName() == clonedHall->getName());
    CHECK(originalHall.getNumberOfRows() == clonedHall->getNumberOfRows());
    CHECK(originalHall.getNumberOfSeats() == clonedHall->getNumberOfSeats());

    delete clonedHall;
}

TEST_CASE("PurchasedTicket - generateUniqueCode") {
    Event event("EventName", Date(2023, 5, 17), "HallName");
    PurchasedTicket ticket1(2, 5, event);
    PurchasedTicket ticket2(3, 7, event);

    CHECK(ticket1.getUniqueCode() != ticket2.getUniqueCode());
    CHECK(ticket1.getUniqueCode().substr(0, 10) == "TR002S005D");
}

TEST_CASE("PurchasedTicket - Clone") {
    Event event("EventName", Date(2023, 5, 17), "HallName");
    PurchasedTicket originalTicket(2, 5, event);
    PurchasedTicket* clonedTicket = originalTicket.clone();

    CHECK(clonedTicket != nullptr);
    CHECK(originalTicket.getRow() == clonedTicket->getRow());
    CHECK(originalTicket.getSeat() == clonedTicket->getSeat());
    CHECK(originalTicket.getEvent() == clonedTicket->getEvent());

    delete clonedTicket;
}

TEST_CASE("Theater constructor creates a single instance") {
    Theater* theater = Theater::getInstance();
    CHECK(theater != nullptr);
    CHECK(theater == Theater::getInstance());
}

TEST_CASE("Theater - Getters") {
    Theater* theater = Theater::getInstance();

    SUBCASE("getHalls") {
        const std::vector<Hall*>& halls = theater->getHalls();
        CHECK(halls.size() == 0); 
    }

    SUBCASE("getEvents") {
        const std::vector<Event*>& events = theater->getEvents();
        CHECK(events.size() == 0); 
    }

    SUBCASE("getBookedTickets") {
        const std::vector<BookedTicket*>& bookedTickets = theater->getBookedTickets();
        CHECK(bookedTickets.size() == 0); 
    }

    SUBCASE("getFreeTickets") {
        const std::vector<Ticket*>& freeTickets = theater->getFreeTickets();
        CHECK(freeTickets.size() == 0);
    }

    SUBCASE("getPurchasedTickets") {
        const std::vector<PurchasedTicket*>& purchasedTickets = theater->getPurchasedTickets();
        CHECK(purchasedTickets.size() == 0);
    }
}

TEST_CASE("Add functions") {
    Date date("2023-02-01");
    Hall* hall = new Hall("Hall 1", 10, 10);
    Event* event = new Event("EventName", date, "Hall 1");
    Theater* theater = Theater::getInstance();
    
    SUBCASE("Adding halls") {
        theater->addHall(hall);
        const std::vector<Hall*>& halls = theater->getHalls();
        CHECK(halls.size() == 1);
    }

    SUBCASE("Adding events") {
        theater->addHall(hall);
        theater->addEvent(date, "Hall 1", "EventName");
        const std::vector<Event*>& events = theater->getEvents();
        CHECK(events.size() == 1);
    }

    SUBCASE("Adding free tickets") {
        theater->addHall(hall);
        theater->addEvent(date, "Hall 1", "EventName");
        makeAllTicketsFree(theater);
        CHECK(theater->getFreeTickets().size() == hall->getNumberOfRows() * hall->getNumberOfSeats());
    }

    theater->free();
    delete hall;
    delete event;
}

TEST_CASE("Theater - bookTicket - booking an available seat") {
    Theater* theater = Theater::getInstance();
    Hall* hall = new Hall("Hall 1", 10, 10);
    Date date("2023-05-01");
    Event* event = new Event("Event 1", date, "Hall 1");
    theater->addHall(hall);
    theater->addEvent(date, "Hall 1", "Event 1");
    makeAllTicketsFree(theater);

    CHECK_NOTHROW(theater->bookTicket(1, 1, date, "Event 1", "Note"));
    CHECK(theater->getBookedTickets().size() == 1);
    CHECK(theater->getFreeTickets().size() == hall->getNumberOfRows() * hall->getNumberOfSeats() - 1);

    theater->free();
    delete hall;
    delete event;
}

TEST_CASE("Theater - bookTicket - Booking an unavailable seat") {
    Theater* theater = Theater::getInstance();
    Hall* hall = new Hall("Hall 1", 10, 10);
    Date date("2023-05-01");
    Event* event = new Event("Event 1", date, "Hall 1");
    theater->addHall(hall);
    theater->addEvent(date, "Hall 1", "Event 1");
    makeAllTicketsFree(theater);

    CHECK_NOTHROW(theater->bookTicket(1, 1, date, "Event 1", "Note"));
    CHECK(theater->getBookedTickets().size() == 1);
    CHECK(theater->getFreeTickets().size() == hall->getNumberOfRows() * hall->getNumberOfSeats() - 1);

    theater->free();
    delete hall;
    delete event;
}

TEST_CASE("Theater - bookTicket - Booking an invalid seat") {
    Theater* theater = Theater::getInstance();
    Hall* hall = new Hall("Hall 1", 10, 10);
    Date date("2023-05-01");
    Event* event = new Event("Event 1", date, "Hall 1");
    theater->addHall(hall);
    theater->addEvent(date, "Hall 1", "Event 1");

    CHECK_THROWS_AS(theater->bookTicket(0, 1, date, "Event 1", "Note"), std::runtime_error);
    CHECK(theater->getBookedTickets().size() == 0);

    theater->free();
    delete hall;
    delete event;
}

TEST_CASE("Theater - bookTicket - Booking a seat for an invalid event") {
    Theater* theater = Theater::getInstance();
    Hall* hall = new Hall("Hall 1", 10, 10);
    Date date("2023-05-01");
    Event* event = new Event("Event 1", date, "Hall 1");
    theater->addHall(hall);
    theater->addEvent(date, "Hall 1", "Event 1");
    CHECK_THROWS_AS(theater->bookTicket(1, 1, date, "Event 2", "Note"), std::runtime_error);
    CHECK(theater->getBookedTickets().size() == 0);

    theater->free();
    delete hall;
    delete event;
}

TEST_CASE("Theater - bookTicket - Booking a seat for an invalid date") {
    Theater* theater = Theater::getInstance();
    Hall* hall = new Hall("Hall 1", 10, 10);
    Date date("2023-05-01");
    Date date2("2023-05-02");
    Event* event = new Event("Event 1", date, "Hall 1");
    theater->addHall(hall);
    theater->addEvent(date, "Hall 1", "Event 1");

    CHECK_THROWS_AS(theater->bookTicket(1, 1, date2, "Event 1", "Note"), std::runtime_error);
    CHECK(theater->getBookedTickets().size() == 0);

    theater->free();
    delete hall;
    delete event;
}

TEST_CASE("Theater - purchaseTicket - Purchasing an available ticket") {
    Theater* theater = Theater::getInstance();
    Hall* hall = new Hall("Hall 1", 10, 10);
    theater->addHall(hall);
    Date date(2023, 5, 1);
    Event* event = new Event("Event 1", date, "Hall 1");
    theater->addEvent(date, "Hall 1", "Event 1");

    Ticket* ticket = new Ticket(1, 1, *event);
    theater->addFree(ticket);

    CHECK_NOTHROW(theater->purchaseTicket(1, 1, date, "Event 1"));
    CHECK(theater->getPurchasedTickets().size() == 1);
    CHECK(theater->getFreeTickets().empty());

    theater->free();
    delete hall;
    delete event;
    delete ticket;
}

TEST_CASE("Theater - purchaseTicket - Purchasing a booked ticket") {
    Theater* theater = Theater::getInstance();
    Hall* hall = new Hall("Hall 1", 10, 10);
    theater->addHall(hall);
    Date date(2023, 5, 1);
    Event* event = new Event("Event 1", date, "Hall 1");
    theater->addEvent(date, "Hall 1", "Event 1");

    Ticket* ticket = new Ticket(1, 1, *event);
    theater->addFree(ticket);
    theater->bookTicket(1, 1, date, "Event 1", "note");

    CHECK_THROWS_AS(theater->purchaseTicket(1, 1, date, "Event 1"), std::runtime_error);
    CHECK(theater->getPurchasedTickets().size() == 0);
    CHECK(theater->getBookedTickets().size() == 1);

    theater->free();
    delete hall;
    delete event;
    delete ticket;
}

TEST_CASE("Theater - unbookTicket - Unbooking a booked ticket") {
    Theater* theater = Theater::getInstance();
    Hall* hall = new Hall("Hall 1", 10, 10);
    theater->addHall(hall);
    Date date(2023, 5, 1);
    Event* event = new Event("Event 1", date, "Hall 1");
    theater->addEvent(date, "Hall 1", "Event 1");

    Ticket* ticket = new Ticket(1, 1, *event);
    theater->addFree(ticket);

    theater->bookTicket(1, 1, date, "Event 1", "note");
    CHECK_NOTHROW(theater->unbookTicket(1, 1, date, "Event 1"));
    CHECK(theater->getBookedTickets().empty());
    CHECK(theater->getFreeTickets().size() == 1);

    theater->free();
    delete hall;
    delete event;
    delete ticket;
}

TEST_CASE("Theater - unbookTicket - Unbooking a non-existing booked ticket") {
    Theater* theater = Theater::getInstance();
    Hall* hall = new Hall("Hall 1", 10, 10);
    theater->addHall(hall);
    Date date(2023, 5, 1);
    Event* event = new Event("Event 1", date, "Hall 1");
    theater->addEvent(date, "Hall 1", "Event 1");

    CHECK_THROWS_AS(theater->unbookTicket(1, 1, date, "Event 1"), std::runtime_error);

    theater->free();
    delete hall;
    delete event;
}

TEST_CASE("Theater - unbookTicket - Unbooking ticket with an invalid row") {
    Theater* theater = Theater::getInstance();
    Hall* hall = new Hall("Hall 1", 10, 10);
    theater->addHall(hall);
    Date date(2023, 5, 1);
    Event* event = new Event("Event 1", date, "Hall 1");
    theater->addEvent(date, "Hall 1", "Event 1");

    CHECK_THROWS_AS(theater->unbookTicket(0, 1, date, "Event 1"), std::runtime_error);
    CHECK_THROWS_AS(theater->unbookTicket(hall->getNumberOfRows() + 1, 1, date, "Event 1"), std::runtime_error);

    theater->free();
    delete hall;
    delete event;
}

TEST_CASE("Ticket constructor and getters") {
    Event event("EventName", Date(2023, 5, 17), "HallName");
    Ticket ticket(2, 5, event);

    CHECK(ticket.getRow() == 2);
    CHECK(ticket.getSeat() == 5);
    CHECK(ticket.getEvent() == event);
}

TEST_CASE("Ticket - PrintTicket") {
    Event event("EventName", Date(2023, 5, 17), "HallName");
    Ticket ticket(2, 5, event);

    std::ostringstream oss;
    std::streambuf* coutBuf = std::cout.rdbuf();    //storing the current buffer of std::cout in coutbuf
    std::cout.rdbuf(oss.rdbuf());                   //redirect the output stream

    ticket.printTicket();

    std::cout.rdbuf(coutBuf);                       //restore the original buffer

    CHECK(oss.str() == "R: 2, S: 5\n");
}

TEST_CASE("Ticket - Clone") {
    Event event("EventName", Date(2023, 5, 17), "HallName");
    Ticket ticket(2, 5, event);
    Ticket* clonedTicket = ticket.clone();

    CHECK(clonedTicket->getRow() == ticket.getRow());
    CHECK(clonedTicket->getSeat() == ticket.getSeat());
    CHECK(clonedTicket->getEvent() == ticket.getEvent());

    delete clonedTicket;
}



int main() 
{
    // Run the tests
    doctest::Context().run();


    Engine::getInstance().start();

    return 0;
}