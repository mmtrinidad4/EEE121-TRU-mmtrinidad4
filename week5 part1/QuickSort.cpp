#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <map>
#include <algorithm>
#include <iterator>
#include <sstream>

using namespace std;

// struct

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

// park sys class

class ParkingSystem {
private:
    vector<VehicleInfo> entries;
    vector<VehicleInfo> departedVehicles;

    void quickSortHelper(int low, int high) {
        if (low < high) {
            int pivotIndex = partition(low, high);
            cout << "PVT-" << entries[pivotIndex].year << " PARTITION: ";
            for (int i = low; i <= high; ++i) {
                cout << entries[i].year << " ";
            }
            cout << endl;

            quickSortHelper(low, pivotIndex - 1);
            quickSortHelper(pivotIndex + 1, high);
        }
    }

    int partition(int low, int high) {
        string pivot = entries[high].year;
        int i = low - 1;

        for (int j = low; j < high; ++j) {
            if (entries[j].year <= pivot) {
                ++i;
                swap(entries[i], entries[j]);
            }
        }

        swap(entries[i + 1], entries[high]);
        return i + 1;
    }

public:
    void recordEntry(const VehicleInfo& vehicle) {
        entries.push_back(vehicle);
        cout << endl;
    }

    //exit
    void recordExit(const string& plateNumber) {
        for (size_t i = 0; i < entries.size(); ++i) {
            if (entries[i].plateNumber == plateNumber) {
                time_t currentTime = time(0);
                entries[i].exitTime = currentTime;
            
                entries[i].cost = calculateParkingCost(entries[i]);

                time_t parkingDuration = entries[i].exitTime - entries[i].entryTime;
                entries[i].hours = static_cast<int>(parkingDuration) / 3600; //3600s in an hour
                if (entries[i].hours == 0) {
                    entries[i].hours = 1;
                }

                departedVehicles.push_back(entries[i]);

                cout << "\n" << entries[i].plateNumber << "," << put_time(localtime(&entries[i].entryTime), "%Y-%m-%d %H:%M:%S") << "," << put_time(localtime(&entries[i].exitTime), "%Y-%m-%d %H:%M:%S") << "," << entries[i].hours << "," << "P" << entries[i].cost << "," << entries[i].brand << "," << entries[i].model << "," << entries[i].year << endl;
            }
        }
    }

    // find
    void findEntry(const string& plateNumber) {
        for (const VehicleInfo& entry : entries) {
            if (entry.plateNumber == plateNumber) {
                cout << entry.plateNumber << "," << put_time(localtime(&entry.entryTime), "%Y-%m-%d %H:%M:%S") << ",NONE,0,P0" << "," << entry.brand << "," << entry.model << "," <<  entry.year << "\n" << endl;
            }
        }
    }

    // database
    void viewDatabase() {
        for (size_t i = 0; i < entries.size(); ++i) {
            if (entries[i].exitTime == 0){
                cout << entries[i].plateNumber << "," << put_time(localtime(&entries[i].entryTime), "%Y-%m-%d %H:%M:%S") << ",NONE,0,P0" << "," << entries[i].brand << "," << entries[i].model << "," <<  entries[i].year << endl;
            }
        }
    }

    // history
    void viewHistoryDatabase(){
        for (size_t i = 0; i < departedVehicles.size(); ++i) {
            cout << entries[i].plateNumber << "," << put_time(localtime(&entries[i].entryTime), "%Y-%m-%d %H:%M:%S") << "," << put_time(localtime(&entries[i].exitTime), "%Y-%m-%d %H:%M:%S") << "," << entries[i].hours << "," << "P" << entries[i].cost << "," << entries[i].brand << "," << entries[i].model << "," <<  entries[i].year << endl;
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

        // BSORT
    void bubbleSort(){
        int iterCount = 0;
        for (int z = (entries.size() - 1); z > 0; --z){
            for (int j = 0; j < z; ++j){
                string x, y;
                x = entries[j].year;
                y = entries[j+1].year;
                int res = x.compare(y);
                if (res > 0){
                    swap(entries[j], entries[j+1]);
                }
            }
            for (size_t i = 0; i < entries.size(); ++i) {
                if (entries[i].exitTime == 0){
                    cout << "ITER-" << iterCount+1 << " : "<< entries[i].plateNumber << "," << put_time(localtime(&entries[i].entryTime), "%Y-%m-%d %H:%M:%S") << ",NONE,0,P0" << "," << entries[i].brand << "," << entries[i].model << "," <<  entries[i].year << endl;
                }
            }
            cout << endl;
            iterCount++;
        }
    }

    // BFIND
    void findBinSearch(const std::string& plateNumber) {
        sort(entries.begin(), entries.end(), [](const VehicleInfo& a, const VehicleInfo& b) {
            return a.plateNumber < b.plateNumber;
        });

        size_t low = 0;
        size_t high = entries.size() - 1;
        int iterCount = 0;
        while (low <= high) {
            size_t mid = low + (high - low) / 2;
            
            if (entries[mid].plateNumber == plateNumber) {
                cout << entries[mid].plateNumber << "," << put_time(localtime(&entries[mid].entryTime), "%Y-%m-%d %H:%M:%S") << ",NONE,0,P0" << "," << entries[mid].brand << "," << entries[mid].model << "," <<  entries[mid].year << endl;
                cout << endl;
                return;
            }

            if (entries[mid].plateNumber < plateNumber) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }

            for (size_t i = low; i <= high; ++i) {
                if (entries[i].exitTime == 0){
                    cout << "MID-" << iterCount+1 << " : "<< entries[i].plateNumber << "," << put_time(localtime(&entries[i].entryTime), "%Y-%m-%d %H:%M:%S") << ",NONE,0,P0" << "," << entries[i].brand << "," << entries[i].model << "," <<  entries[i].year << endl;
                }
            }
            iterCount += 1;
            cout << endl;

        }

        cout << "CAR NOT FOUND" << endl;
    }

    // QSORT
    void quickSort() {
        quickSortHelper(0, entries.size() - 1);

        cout << "\nSORTED LIST: ";
        cout << endl;
        for (const auto& entry : entries) {
            cout << entry.year << " ";
        }
        cout << endl;
    }
};

// MAIN
int main(){
    srand(time(nullptr));

    string input;
    ParkingSystem parkingSystem;

    while (true) {
        cout << "> ";
        getline(cin, input);

        cout << input << endl;

        stringstream ss(input);
        string command;
        ss >> command;

        if (command == "PARK"){
            string plate, brand, model, year;
            VehicleInfo newEntry;
            if (!(ss >> plate >> brand >> model >> year)){
                cout << "\nUNSUPPORTED COMMAND\n" << endl;
            }
            else{
                newEntry.plateNumber = plate;
                newEntry.brand = brand;
                newEntry.model = model;
                newEntry.year = year;
                newEntry.entryTime = time(0); 
                parkingSystem.recordEntry(newEntry);
            }
        }
        else if (command == "LIST") {
            cout << "\n";
            cout << endl;
            parkingSystem.viewDatabase();
        }
        
        else if (command == "FIND"){
            string plate;
            if (!(ss>>plate)){
                cout << "\nUNSUPPORTED COMMAND\n" << endl;
                cout << endl;
            }
            else {
                parkingSystem.findEntry(plate);
            }
        }

        else if (command == "EXIT"){
            string plate;
            if (!(ss>>plate)){
                cout << "\nUNSUPPORTED COMMAND\n" << endl;
                cout << endl;
            }
            else{
                parkingSystem.recordExit(plate);
            }
        }

        else if (command == "LOG"){
            cout << "\n";
            cout << endl;
            parkingSystem.viewHistoryDatabase();
        }

        else if (command == "BSORT"){
            cout << "\n";
            cout << endl;
            parkingSystem.bubbleSort();
        }

        else if (command == "BFIND"){
            string plate;
            if (!(ss>>plate)){
                cout << "\nUNSUPPORTED COMMAND\n" << endl;
                cout << endl;
            }
            else {
                parkingSystem.findBinSearch(plate);
            }
        }

        else if (command == "QSORT"){
            cout << "\n";
            cout << endl;
            parkingSystem.quickSort();
        }

        else if (command == "QUIT") {
            break;
        }

        else {
            cout << "\nUNSUPPORTED COMMAND\n" << endl;
        }
    }
    return 0;
}