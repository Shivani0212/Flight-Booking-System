#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Flight {
public:
    string ID, source, destination;
    int capacity;
    int booked;

    Flight() : capacity(0), booked(0) {}

    Flight(string id, string src, string dest, int cap)
        : ID(id), source(src), destination(dest), capacity(cap), booked(0) {}

    bool bookSeat() {
        if (booked < capacity) {
            booked++;
            return true;
        }
        return false;
    }

    void displayInfo() const {
        cout << "Flight ID: " << ID
             << ", From: " << source
             << ", To: " << destination
             << ", Capacity: " << capacity
             << ", Booked: " << booked << endl;
    }
};

class User {
public:
    string email, firstName, lastName;
    vector<string> bookings;  // Stores flight IDs

    User() {}

    User(string e, string f, string l)
        : email(e), firstName(f), lastName(l) {}

    void addBooking(const string& flightID) {
        bookings.push_back(flightID);
    }

    void viewBookings() const {
        cout << "Bookings for " << firstName << " " << lastName << " (" << email << "):" << endl;
        if (bookings.empty()) {
            cout << "No bookings found." << endl;
        } else {
            for (const string& id : bookings) {
                cout << "- " << id << endl;
            }
        }
    }
};

class BookingSystem {
private:
    unordered_map<string, Flight> flights;
    unordered_map<string, User> users;

public:
    // Admin function
    void addFlight(const string& id, const string& src, const string& dest, int cap) {
        if (flights.find(id) != flights.end()) {
            cout << "Flight ID already exists.\n";
            return;
        }
        flights[id] = Flight(id, src, dest, cap);
        cout << "Flight added successfully.\n";
    }

    // User registration
    void registerUser(const string& email, const string& fname, const string& lname) {
        if (users.find(email) != users.end()) {
            cout << "User already registered.\n";
            return;
        }
        users[email] = User(email, fname, lname);
        cout << "User registered successfully.\n";
    }

    // Booking
    void bookFlight(const string& email, const string& flightID) {
        if (users.find(email) == users.end()) {
            cout << "User not found.\n";
            return;
        }
        if (flights.find(flightID) == flights.end()) {
            cout << "Flight not found.\n";
            return;
        }

        Flight& flight = flights[flightID];
        if (flight.bookSeat()) {
            users[email].addBooking(flightID);
            cout << "Booking successful.\n";
        } else {
            cout << "Flight is fully booked.\n";
        }
    }

    void viewUserBookings(const string& email) const {
        auto it = users.find(email);
        if (it != users.end()) {
            it->second.viewBookings();
        } else {
            cout << "User not found.\n";
        }
    }

    void listAllFlights() const {
        cout << "Available Flights:\n";
        for (const auto& pair : flights) {
            pair.second.displayInfo();
        }
    }
};

// Sample interaction
int main() {
    BookingSystem system;

    // Admin adds flights
    system.addFlight("FL101", "New York", "London", 3);
    system.addFlight("FL102", "Paris", "Berlin", 2);

    // Register users
    system.registerUser("john@example.com", "John", "Doe");
    system.registerUser("jane@example.com", "Jane", "Smith");

    // Bookings
    system.bookFlight("john@example.com", "FL101");
    system.bookFlight("john@example.com", "FL102");
    system.bookFlight("jane@example.com", "FL101");
    system.bookFlight("jane@example.com", "FL101"); // Attempting again to check capacity

    // View bookings
    system.viewUserBookings("john@example.com");
    system.viewUserBookings("jane@example.com");

    // List flights
    system.listAllFlights();

    return 0;
}