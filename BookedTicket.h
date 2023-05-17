#include "Ticket.h"

class BookedTicket : public Ticket {
private:
    string note;

public:
    BookedTicket(int row, int seat, const Event& event, const string note); //parametric constructor

    Ticket* clone() override final;

    //Getter
    const string& getNote() const;
};