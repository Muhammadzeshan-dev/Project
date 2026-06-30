#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

const int MAX_VEHICLES = 100;

class Vehicle {
protected:
    string id;
    string brand;
    string model;
    bool available;

public:
    Vehicle() {}
    Vehicle(string i, string b, string m, bool a = true) : id(i), brand(b), model(m), available(a) {}
    virtual void display() = 0;
    virtual string toFileString() = 0;
    string getId() {
        return id;
    }
    bool isAvailable() {
        return available;
    }
    void rent() {
        available = false;
    }
    void makeAvailable() {
        available = true;
    }
    virtual string getType() = 0;
};

class Car : public Vehicle {
    int numDoors;

public:
    Car() {}
    Car(string i, string b, string m, int d, bool a = true) : Vehicle(i, b, m, a), numDoors(d) {}
    void display() override {
        cout << "+-----------------------------------------------------+" << endl;
        cout << "| ID          :  " << id << endl;
        cout << "| Type        :  Car" << endl;
        cout << "| Brand       :  " << brand << endl;
        cout << "| Model       :  " << model << endl;
        cout << "| Doors       :  " << numDoors << endl;
        cout << "| Available   :  " << (available ? "Yes" : "No") << endl;
    }
    string toFileString() override {
        return "Car," + id + "," + brand + "," + model + "," + to_string(numDoors) + "," + (available ? "1" : "0");
    }
    string getType() override {
        return "Car";
    }
};

class Bike : public Vehicle {
    string type;

public:
    Bike() {}
    Bike(string i, string b, string m, string t, bool a = true) : Vehicle(i, b, m, a), type(t) {}
    void display() override {
        cout << "+-----------------------------------------------------+" << endl;
        cout << "| ID          :  " << id << endl;
        cout << "| Type        :  Bike" << endl;
        cout << "| Brand       :  " << brand << endl;
        cout << "| Model       :  " << model << endl;
        cout << "| Style       :  " << type << endl;
        cout << "| Available   :  " << (available ? "Yes" : "No") << endl;
    }
    string toFileString() override {
        return "Bike," + id + "," + brand + "," + model + "," + type + "," + (available ? "1" : "0");
    }
    string getType() override {
        return "Bike";
    }
};

class Truck : public Vehicle {
    double capacity;

public:
    Truck() {}
    Truck(string i, string b, string m, double c, bool a = true) : Vehicle(i, b, m, a), capacity(c) {}
    void display() override {
        cout << "+-----------------------------------------------------+" << endl;
        cout << "| ID          :  " << id << endl;
        cout << "| Type        :  Truck" << endl;
        cout << "| Brand       :  " << brand << endl;
        cout << "| Model       :  " << model << endl;
        cout << "| Capacity    :  " << capacity << " tons" << endl;
        cout << "| Available   :  " << (available ? "Yes" : "No") << endl;
    }
    string toFileString() override {
        return "Truck," + id + "," + brand + "," + model + "," + to_string(capacity) + "," + (available ? "1" : "0");
    }
    string getType() override {
        return "Truck";
    }
};

Vehicle* vehicles[MAX_VEHICLES];
int countVehicles = 0;

void printHeader() {
    cout << "\n*****************************************\n";
    cout << "*   RENTAL VEHICLE MANAGEMENT SYSTEM   *\n";
    cout << "*****************************************\n";
}

void saveToFile() {
    ofstream out("vehicles.txt");
    for (int i = 0; i < countVehicles; i++) {
        out << vehicles[i]->toFileString() << endl;
    }
    out.close();
}

void loadFromFile() {
    ifstream in("vehicles.txt");
    string line;
    while (getline(in, line)) {
        string type, id, brand, model, attr, availStr;
        size_t pos = 0;

        pos = line.find(','); type = line.substr(0, pos); line.erase(0, pos + 1);
        pos = line.find(','); id = line.substr(0, pos); line.erase(0, pos + 1);
        pos = line.find(','); brand = line.substr(0, pos); line.erase(0, pos + 1);
        pos = line.find(','); model = line.substr(0, pos); line.erase(0, pos + 1);
        pos = line.find(','); attr = line.substr(0, pos); line.erase(0, pos + 1);
        availStr = line;

        bool avail = (availStr == "1");
        if (type == "Car")
            vehicles[countVehicles++] = new Car(id, brand, model, atoi(attr.c_str()), avail);
        else if (type == "Bike")
            vehicles[countVehicles++] = new Bike(id, brand, model, attr, avail);
        else if (type == "Truck")
            vehicles[countVehicles++] = new Truck(id, brand, model, atof(attr.c_str()), avail);
    }
    in.close();
}

int findVehicleIndex(string id) {
    for (int i = 0; i < countVehicles; i++) {
        if (vehicles[i]->getId() == id) return i;
    }
    return -1;
}

int main() {
    loadFromFile();
    int choice;
    do {
        printHeader();
        cout << "1. Add Vehicle\n2. Display All Vehicles\n3. Display Available Vehicles\n";
        cout << "4. Rent Vehicle\n5. Return Vehicle\n6. Exit\n";
        cout << "-----------------------------------------------------\n";
        cout << "Choose an option : ";
        cin >> choice;
        cout << endl;

        if (choice == 1) {
            int type;
            cout << "Enter Vehicle type (1-Car, 2-Bike, 3-Truck): ";
            cin >> type;
            string id, brand, model;
            cout << "Enter ID: "; cin >> id;
            cout << "Enter Brand: "; cin >> brand;
            cout << "Enter Model: "; cin >> model;

            if (type == 1) {
                int doors;
                cout << "Enter number of doors: "; cin >> doors;
                vehicles[countVehicles++] = new Car(id, brand, model, doors);
            }
            else if (type == 2) {
                string style;
                cout << "Enter bike style: "; cin >> style;
                vehicles[countVehicles++] = new Bike(id, brand, model, style);
            }
            else if (type == 3) {
                double cap;
                cout << "Enter capacity (tons): "; cin >> cap;
                vehicles[countVehicles++] = new Truck(id, brand, model, cap);
            }
            else {
                cout << "Invalid Type!" << endl;
                continue;
            }
            saveToFile();
            cout << "Vehicle added successfully.\n";
        }

        else if (choice == 2) {
            for (int i = 0; i < countVehicles; i++)
                vehicles[i]->display();
        }

        else if (choice == 3) {
            for (int i = 0; i < countVehicles; i++) {
                if (vehicles[i]->isAvailable())
                    vehicles[i]->display();
            }
        }

        else if (choice == 4) {
            string id;
            cout << "Enter vehicle ID to rent: ";
            cin >> id;
            int index = findVehicleIndex(id);
            if (index != -1) {
                if (vehicles[index]->isAvailable()) {
                    vehicles[index]->rent();
                    saveToFile();
                    cout << "Vehicle rented successfully.\n";
                } else {
                    cout << "Vehicle is already rented.\n";
                }
            } else {
                cout << "Vehicle not found.\n";
            }
        }

        else if (choice == 5) {
            string id;
            cout << "Enter vehicle ID to return: ";
            cin >> id;
            int index = findVehicleIndex(id);
            if (index != -1) {
                if (!vehicles[index]->isAvailable()) {
                    vehicles[index]->makeAvailable();
                    saveToFile();
                    cout << "Vehicle returned successfully.\n";
                } else {
                    cout << "Vehicle was not rented.\n";
                }
            } else {
                cout << "Vehicle not found.\n";
            }
        }

        else if (choice != 6) {
            cout << "Invalid choice.\n";
        }

        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
        system("cls");

    } while (choice != 6);

    cout << "Exiting system. Goodbye!\n";
    return 0;
}
