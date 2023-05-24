# Tickets
## Project for the OOP course at FMI

The Information System is a command-line application designed to manage theater-related data such as halls, events, and tickets. It provides functionalities for adding halls, creating events, booking and purchasing tickets, generating reports, and more.

## Features

- **Halls Management:** Add and manage different halls available in the theater.
- **Event Creation:** Create events specifying the date, hall, and event name.
- **Ticket Booking:** Book tickets for specific events, seat numbers, and additional notes.
- **Ticket Purchase:** Purchase tickets for specific events and seat numbers.
- **Ticket Cancellation:** Cancel booked tickets and make them available again.
- **Reports Generation:** Generate reports on ticket sales, bookings, and available seats for specific periods and halls.
- **Statistics:** View statistics on the most watched events based on purchased tickets count.

## Usage

1. Launch the program.
2. Follow the command-line prompts to perform various actions such as adding halls, creating events, booking/purchasing tickets, generating reports, and viewing statistics.
3. Enter the required information as prompted to execute the desired functionality.
4. Follow the program's instructions and on-screen messages for successful execution of commands.

## Dependencies

The program depends on the following libraries:

- [Nlohmann JSON](https://github.com/nlohmann/json): A C++ library for JSON serialization and deserialization.

## Future Development and Enhancements

### Seat Selection

Enhance the ticket booking process by implementing a seat selection feature. Users will be able to visually select seats from an interactive seat map during the booking process.

### Ticket Pricing

Introduce dynamic ticket pricing to provide flexible pricing options for events. The system will calculate ticket prices based on various factors such as event popularity, seat location, or special promotions.

### User Authentication

Enhance the system's security and user management capabilities by implementing a user authentication system. Users will be required to log in with credentials, and different user roles (e.g., administrators, employees, customers) will have different levels of access and privileges.

### Ticket QR Code

Integrate a QR code generation feature for purchased tickets. Each ticket will have a unique QR code, and users can conveniently present their tickets for validation by scanning the QR code.

### Event Types

Enhance the system by introducing different types of events. Users will be able to specify the type of event (e.g., movie, play, concert) during event creation, providing more variety and flexibility in managing different types of performances.

## Example Data

To provide a starting point and demonstrate the functionality of the Information System Program, you can use the following example JSON data:

```json
{
  "halls": [
    {
      "name": "A",
      "numRows": 10,
      "numSeats": 15
    },
    {
      "name": "B",
      "numRows": 8,
      "numSeats": 12
    }
  ],
  "events": [
    {
      "date": "2022-02-02",
      "hallName": "B",
      "eventName": "Event X"
    },
    {
      "date": "2022-02-02",
      "hallName": "A",
      "eventName": "Event Y"
    },
    {
      "date": "2022-01-01",
      "hallName": "B",
      "eventName": "Event Z"
    }
  ],
  "bookedTickets": [
    {
      "row": 5,
      "seat": 10,
      "note": "Special request",
      "date": "2022-02-02",
      "eventName": "Event X",
      "hallName":"B"
    }
  ],
  "purchasedTickets": [
    {
      "row": 6,
      "seat": 12,
      "eventName": "Event Z",
      "hallName": "B",
      "date": "2022-01-01"
    }
  ]
}



