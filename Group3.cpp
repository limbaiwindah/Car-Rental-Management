// Car Rental Management Program
// Group 3 - CCP4213 Assignment

#include <iostream>
#include <string>
using namespace std;

// Structure for Car
struct Car {
    int carID;
    string model;
    string plateNo;
    bool isRented;
    Car* next;
};

// Structure for Customer
struct Customer {
    int custID;
    string name;
    Customer* next;
};

// Queue for Rental Requests (array implementation)
const int MAX_QUEUE = 10;
struct RentalRequest {
    int custID;
    int carID;
};
class RentalQueue {
    RentalRequest queue[MAX_QUEUE];
    int front, rear;
public:
    RentalQueue() : front(0), rear(0) {}
    bool isFull() { return ((rear + 1) % MAX_QUEUE == front); }
    bool isEmpty() { return (front == rear); }
    bool enqueue(int custID, int carID) {
        if (isFull()) return false;
        queue[rear].custID = custID;
        queue[rear].carID = carID;
        rear = (rear + 1) % MAX_QUEUE;
        return true;
    }
    bool dequeue(RentalRequest &req) {
        if (isEmpty()) return false;
        req = queue[front];
        front = (front + 1) % MAX_QUEUE;
        return true;
    }
    void display() {
        cout << "Rental Requests in Queue:\n";
        if (isEmpty()) cout << "Queue is empty.\n";
        else {
            int i = front;
            while (i != rear) {
                cout << "- Customer ID: " << queue[i].custID
                     << " | Car ID: " << queue[i].carID << endl;
                i = (i + 1) % MAX_QUEUE;
            }
        }
    }
};

// Main Class
class CarRentalSystem {
    Car* carHead;
    Customer* custHead;
    RentalQueue rentalQ;
    int carCount, custCount;
public:
    CarRentalSystem() : carHead(NULL), custHead(NULL), carCount(0), custCount(0) {}

    // --------- CAR MANAGEMENT ---------
    void addCar() {
        Car* newCar = new Car;
        newCar->carID = ++carCount;
        cout << "Enter model: "; cin >> ws; getline(cin, newCar->model);
        cout << "Enter plate number: "; getline(cin, newCar->plateNo);
        newCar->isRented = false;
        newCar->next = carHead;
        carHead = newCar;
        cout << "Car added successfully!\n";
    }
    void editCar() {
        int id; cout << "Enter Car ID to edit: "; cin >> id;
        Car* car = findCarByID(id);
        if (!car) { cout << "Car not found!\n"; return; }
        cout << "Edit model (current: " << car->model << "): "; cin >> ws; getline(cin, car->model);
        cout << "Edit plate number (current: " << car->plateNo << "): "; getline(cin, car->plateNo);
        cout << "Edit status (0=Available, 1=Rented): "; cin >> car->isRented;
        cout << "Car updated successfully!\n";
    }
    void deleteCar() {
        int id; cout << "Enter Car ID to delete: "; cin >> id;
        Car *prev = NULL, *curr = carHead;
        while (curr && curr->carID != id) { prev = curr; curr = curr->next; }
        if (!curr) { cout << "Car not found!\n"; return; }
        if (curr->isRented) {
            cout << "Cannot delete a rented car!\n";
            return;
        }
        if (!prev) carHead = curr->next;
        else prev->next = curr->next;
        delete curr;
        cout << "Car deleted successfully!\n";
    }
    void displayCars() {
        cout << "\nList of Cars:\n";
        if (!carHead) { cout << "No cars in the system.\n"; return; }
        bubbleSortCars();
        Car* temp = carHead;
        while (temp) {
            cout << "ID: " << temp->carID << " | Model: " << temp->model
                 << " | Plate: " << temp->plateNo
                 << " | Status: " << (temp->isRented ? "Rented" : "Available") << endl;
            temp = temp->next;
        }
    }
    void searchCar() {
        string plate;
        cout << "Enter plate number to search: "; cin >> ws; getline(cin, plate);
        Car* car = carHead;
        bool found = false;
        while (car) {
            if (car->plateNo == plate) {
                cout << "Found! ID: " << car->carID << " | Model: " << car->model
                     << " | Status: " << (car->isRented ? "Rented" : "Available") << endl;
                found = true;
            }
            car = car->next;
        }
        if (!found) cout << "No car found with that plate number.\n";
    }
    Car* findCarByID(int id) {
        Car* car = carHead;
        while (car) { if (car->carID == id) return car; car = car->next; }
        return NULL;
    }
    // Helper function to find customer by ID
    Customer* findCustomerByID(int id) {
        Customer* cust = custHead;
        while (cust) { if (cust->custID == id) return cust; cust = cust->next; }
        return NULL;
    }
    void bubbleSortCars() {
        if (!carHead) return;
        bool swapped;
        do {
            swapped = false;
            Car* curr = carHead;
            while (curr->next) {
                if (curr->model > curr->next->model) {
                    // swap data
                    swap(curr->carID, curr->next->carID);
                    swap(curr->model, curr->next->model);
                    swap(curr->plateNo, curr->next->plateNo);
                    swap(curr->isRented, curr->next->isRented);
                    swapped = true;
                }
                curr = curr->next;
            }
        } while (swapped);
    }

    // --------- CUSTOMER MANAGEMENT ---------
    void addCustomer() {
        Customer* newCust = new Customer;
        newCust->custID = ++custCount;
        cout << "Enter customer name: "; cin >> ws; getline(cin, newCust->name);
        newCust->next = custHead;
        custHead = newCust;
        cout << "Customer added!\n";
    }
    void displayCustomers() {
        cout << "\nList of Customers:\n";
        if (!custHead) { cout << "No customers in the system.\n"; return; }
        Customer* temp = custHead;
        while (temp) {
            cout << "ID: " << temp->custID << " | Name: " << temp->name << endl;
            temp = temp->next;
        }
    }

    // --------- RENTAL REQUEST (QUEUE) ---------
    void rentCar() {
        int custID, carID;
        cout << "Enter Customer ID: "; cin >> custID;
        Customer* cust = findCustomerByID(custID);
        if (!cust) { cout << "Customer not found.\n"; return; }
        cout << "Enter Car ID to rent: "; cin >> carID;
        Car* car = findCarByID(carID);
        if (!car) { cout << "Car not found.\n"; return; }
        if (car->isRented) { cout << "Car already rented!\n"; return; }
        if (rentalQ.enqueue(custID, carID))
            cout << "Rental request queued successfully!\n";
        else
            cout << "Rental queue is full. Try again later.\n";
    }
    void processRentalRequests() {
        RentalRequest req;
        if (!rentalQ.dequeue(req)) {
            cout << "No pending rental requests.\n"; return;
        }
        Car* car = findCarByID(req.carID);
        if (!car) { cout << "Car not found.\n"; return; }
        if (car->isRented) { cout << "Car already rented!\n"; return; }
        car->isRented = true;
        cout << "Rental processed: Customer ID " << req.custID
             << " now rents Car ID " << req.carID << endl;
    }
    void displayRentalQueue() { rentalQ.display(); }

    // --------- MENU ---------
    void menu() {
        int choice;
        do {
            cout << "\n--- CAR RENTAL MANAGEMENT ---\n"
                 << "1. Add Car\n2. Edit Car\n3. Delete Car\n4. Display Cars\n5. Search Car\n"
                 << "6. Add Customer\n7. Display Customers\n"
                 << "8. Rent Car (add to queue)\n9. Process Rental Requests\n10. Display Rental Queue\n"
                 << "0. Exit\nEnter choice: ";
            cin >> choice;
            switch (choice) {
                case 1: addCar(); break;
                case 2: editCar(); break;
                case 3: deleteCar(); break;
                case 4: displayCars(); break;
                case 5: searchCar(); break;
                case 6: addCustomer(); break;
                case 7: displayCustomers(); break;
                case 8: rentCar(); break;
                case 9: processRentalRequests(); break;
                case 10: displayRentalQueue(); break;
                case 0: cout << "Goodbye!\n"; break;
                default: cout << "Invalid option!\n";
            }
        } while (choice != 0);
    }
};

int main() {
    CarRentalSystem crms;
    crms.menu();
    return 0;
}