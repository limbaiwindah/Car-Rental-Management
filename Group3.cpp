// Car Rental Management Program
// Group 3 - CCP4213 Assignment

/*
SIDE NOTE:
Goal: Temporarily rent cars to customers.
Focus: Rental duration, return dates, renter details, car availability.
Data needed:
    Car: plate number, type, availability
    Renter: name, ID, phone
    Rental info: date, duration, cost
*/

#include <iostream>
#include <string>
using namespace std;

// structs

// Car details
struct Car {
    string carID;
    string carModel, carPlate;
    bool isAvailable; // true = available for rent, false = currently rented
    double dailyRate; // daily rate of car rental
};

// Stores information about customers who rent cars
struct Customer {
    string custID, custName, custTelNum;
};

// Keeps track of rental transactions, linking cars and customers with rental dates
struct Rental {
    string carID;
    string custID;
    string rentalDate, returnDate;
    double totalRentalPrice;
};

// classes


int main() 
{
    

}