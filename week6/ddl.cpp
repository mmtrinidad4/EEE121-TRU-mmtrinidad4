#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>

using namespace std;

// VEHICLE INFO
struct VehicleInfo {
    string plateNumber;
    string brand;
    string model;
    string year;
    time_t entryTime;
    time_t exitTime;
    int hours = 0;
    double cost;
    int intYear;
};

// PARKENTRYNODE CLASS
template<typename S>
class ParkEntryNode {
public:
    S data;
    ParkEntryNode<S>* next;
    ParkEntryNode<S>* prev;
    ParkEntryNode(S data, ParkEntryNode* next = nullptr, ParkEntryNode* prev = nullptr);
};

template<typename S>
ParkEntryNode<S>::ParkEntryNode(S data, ParkEntryNode* next, ParkEntryNode* prev) : data(data), next(next), prev(prev) {}

// PARKENTRYLIST CLASS
template<typename T>
class ParkEntryList {
private:
    ParkEntryNode<T>* head;
    ParkEntryNode<T>* tail;
    int size;
public:
    ParkEntryList();
    void addBack(T val);
    T removeFront();
    T front();
    int getSize();
};

template<typename T>
ParkEntryList<T>::ParkEntryList() : size(0) {
    head = new ParkEntryNode<T>(T(), nullptr, nullptr);
    tail = new ParkEntryNode<T>(T(), nullptr, head);
    head->next = tail;
}

template<typename T>
void ParkEntryList<T>::addBack(T val) {
    ParkEntryNode<T>* newNode = new ParkEntryNode<T>(val, tail, tail->prev);
    tail->prev->next = newNode;
    tail->prev = newNode;
    size++;
}

template<typename T>
T ParkEntryList<T>::removeFront() {
    if (size == 0) {
        throw runtime_error("UNSUPPORTED COMMAND");
    }
    ParkEntryNode<T>* temp = head->next;
    head->next = temp->next;
    temp->next->prev = head;
    T data = temp->data;
    delete temp;
    size--;
    return data;
}

template<typename T>
T ParkEntryList<T>::front() {
    if (size == 0) {
        throw runtime_error("UNSUPPORTED COMMAND");
    }
    return head->next->data;
}

template<typename T>
int ParkEntryList<T>::getSize() {
    return size;
}

// PARKING SYSTEM CLASS
class ParkingSystem {
private:
    ParkEntryList<VehicleInfo> entries;
    ParkEntryList<VehicleInfo> departedVehicles;
    const int MAX_PARKING_CAPACITY = 50;
    const int PARKING_HISTORY_CAPACITY = 100;

public:
    void recordEntry(const VehicleInfo& vehicle) {
        if (entries.getSize() >= MAX_PARKING_CAPACITY) {
            cout << "PARKING FULL" << endl;
            return;
        }
        entries.addBack(vehicle);
    }

    void recordExit(const string& plateNumber) {
        for (size_t i = 0; i < entries.getSize(); ++i) {
            if (entries.front().plateNumber == plateNumber) {
                VehicleInfo vehicle = entries.removeFront();
                time_t currentTime = time(0);
                vehicle.exitTime = currentTime;

                vehicle.cost = calculateParkingCost(vehicle);

                time_t parkingDuration = vehicle.exitTime - vehicle.entryTime;
                vehicle.hours = static_cast<int>(parkingDuration) / 3600; // 3600s in an hour
                if (vehicle.hours == 0) {
                    vehicle.hours = 1;
                }

                departedVehicles.addBack(vehicle);

                cout << "\n" << vehicle.plateNumber << "," << put_time(localtime(&vehicle.entryTime), "%Y-%m-%d %H:%M:%S") << "," << put_time(localtime(&vehicle.exitTime), "%Y-%m-%d %H:%M:%S") << "," << vehicle.hours << "," << "P" << vehicle.cost << "," << vehicle.brand << "," << vehicle.model << "," << vehicle.year << endl;
                return;
            } else {
                entries.addBack(entries.removeFront());
            }
        }
        cout << "CAR NOT FOUND" << endl;
    }

    void findEntry(const string& plateNumber) {
        for (size_t i = 0; i < entries.getSize(); ++i) {
            if (entries.front().plateNumber == plateNumber) {
                VehicleInfo entry = entries.front();
                cout << entry.plateNumber << "," << put_time(localtime(&entry.entryTime), "%Y-%m-%d %H:%M:%S") << ",NONE,0,P0" << "," << entry.brand << "," << entry.model << "," << entry.year << "\n" << endl;
                return;
            } else {
                entries.addBack(entries.removeFront());
            }
        }
        cout << "CAR NOT FOUND" << endl;
    }

    void viewDatabase() {
        for (size_t i = 0; i < entries.getSize(); ++i) {
            VehicleInfo entry = entries.front();
            if (entry.exitTime == 0) {
                cout << entry.plateNumber << "," << put_time(localtime(&entry.entryTime), "%Y-%m-%d %H:%M:%S") << ",NONE,0,P0" << "," << entry.brand << "," << entry.model << "," << entry.year << endl;
            }
            entries.addBack(entries.removeFront());
        }
    }

    void viewHistoryDatabase() {
        for (size_t i = 0; i < departedVehicles.getSize(); ++i) {
            VehicleInfo entry = departedVehicles.front();
            cout << entry.plateNumber << "," << put_time(localtime(&entry.entryTime), "%Y-%m-%d %H:%M:%S") << "," << put_time(localtime(&entry.exitTime), "%Y-%m-%d %H:%M:%S") << "," << entry.hours << "," << "P" << entry.cost << "," << entry.brand << "," << entry.model << "," << entry.year << endl;
            departedVehicles.addBack(departedVehicles.removeFront());
        }
    }

    double calculateParkingCost(const VehicleInfo& vehicle) {
        time_t parkingDuration = vehicle.exitTime - vehicle.entryTime;
        int hours = static_cast<int>(parkingDuration) / 3600;

        double cost = 50.0;

        if (hours > 3) {
            cost += (hours - 3) * 20.0;
        }

        return cost;
    }
};

// MAIN FUNCTION
int main() {
    srand(time(nullptr));

    string input;
    ParkingSystem parkingSystem;

    while (true) {
        cout << "> ";
        getline(cin, input);

        stringstream ss(input);
        string command;
        ss >> command;

        if (command == "PARK") {
            string plate, brand, model, year;
            VehicleInfo newEntry;
            if (!(ss >> plate >> brand >> model >> year)) {
                cout << "\nUNSUPPORTED COMMAND\n" << endl;
                cout << endl;
            } else {
                newEntry.plateNumber = plate;
                newEntry.brand = brand;
                newEntry.model = model;
                newEntry.year = year;
                newEntry.entryTime = time(0);
                parkingSystem.recordEntry(newEntry);
            }
        } else if (command == "LIST") {
            cout << "\n";
            parkingSystem.viewDatabase();
            cout << endl;
        } else if (command == "FIND") {
            string plate;
            if (!(ss >> plate)) {
                cout << "\nUNSUPPORTED COMMAND\n" << endl;
                cout << endl;
            } else {
                parkingSystem.findEntry(plate);
                cout << endl;
            }
        } else if (command == "EXIT") {
            string plate;
            if (!(ss >> plate)) {
                cout << "\nUNSUPPORTED COMMAND\n" << endl;
                cout << endl;
            } else {
                parkingSystem.recordExit(plate);
                cout << endl;
            }
        } else if (command == "LOG") {
            cout << "\n";
            parkingSystem.viewHistoryDatabase();
            cout << endl;
        } else if (command == "QUIT") {
            break;
        } else {
            cout << "\nUNSUPPORTED COMMAND\n" << endl;
        }
    }

    return 0;
}
