// PARK-SIM

#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <iomanip>

using namespace std;

// 500
const int max_main_entries = 500;

//1000
const int max_history_entries = 1000;

class Parking_Entry {

// priv
private:
    string plate;
    string brand;
    string model;
    int year;
    time_t entry_Time;
    time_t exit_Time;
    int totalHours;
    int totalCost;

// pub
public:
    Parking_Entry(string plate, string brand, string model, int year)
        : plate(plate), brand(brand), model(model), year(year), entry_Time(time(nullptr)), exit_Time(0), totalCost(0), totalHours(0) {}

// PLATE TIME: EXIT AND ENTRY
// TOTAL HOURS COST

    string get_Plate() const {
        return plate;
    }

    time_t getEntry_Time() const {
        return entry_Time;
    }

    time_t getExit_Time() const {
        return exit_Time;
    }

    void setExit_Time(time_t exit_Time) {
        this->exit_Time = exit_Time;
    }

    int getTotalHours() const {
        return totalHours;
    }

    void setTotalHours(int totalHours) {
        this->totalHours = totalHours;
    }

    int getTotalCost() const {
        return totalCost;
    }

    void setTotalCost(int totalCost) {
        this->totalCost = totalCost;
    }

    string getBrand() const {
        return brand;
    }

    string getModel() const {
        return model;
    }

    int getYear() const {
        return year;
    }
};

class ParkingSystem {
private:
    vector<Parking_Entry> mainDatabase;
    vector<Parking_Entry> historyDatabase;


public:

// PARK
    void park(string plate, string brand, string model, int year) {
        if (mainDatabase.size() >= max_main_entries) {
            cout << "UNSUPPORTED COMMAND" << endl;
            return;
        }

        Parking_Entry newEntry(plate, brand, model, year);
        mainDatabase.push_back(newEntry);
        cout << "PARK " << plate << " " << brand << " " << model << " " << year << endl;
        cout << endl;
    }


// EXIT COMMAND
    void exit(string plate) {
        auto it = find_if(mainDatabase.begin(), mainDatabase.end(), [&](const Parking_Entry& entry) { return entry.get_Plate() == plate; });

        if (it != mainDatabase.end()) {
            time_t currentTime = time(nullptr);
            it->setExit_Time(currentTime);
            int totalHours = max(1, static_cast<int>((difftime(it->getExit_Time(), it->getEntry_Time()) + 3599) / 3600)); // 3600s in an hour
            int totalCost = 50 + max(0, totalHours - 3) * 20;
            it->setTotalHours(totalHours);
            it->setTotalCost(totalCost);

            Parking_Entry historyEntry = *it;
            historyDatabase.push_back(historyEntry);
            mainDatabase.erase(it);
            cout << "EXIT " << plate << endl;
            cout << endl;
            cout << plate << "," << formatTime(historyEntry.getEntry_Time()) << ","
                 << (historyEntry.getExit_Time() == 0 ? "NONE" : formatTime(historyEntry.getExit_Time())) << ","
                 << historyEntry.getTotalHours() << ","
                 << "P" << historyEntry.getTotalCost() << "," << formatEntryDate(historyEntry.getEntry_Time()) << ","
                 << historyEntry.getBrand() << "," << historyEntry.getModel() << "," << historyEntry.getYear() << endl;
            cout << endl;
        } else {
            cout << endl;
            cout << "CAR NOT FOUND" << endl;
            cout << endl;
        }
    }

// FIND COMMAND
    void find(string plate) {
        auto it = find_if(mainDatabase.begin(), mainDatabase.end(), [&](const Parking_Entry& entry) { return entry.get_Plate() == plate; });

        if (it != mainDatabase.end()) {
            cout << "FIND " << plate << endl;
            cout << endl;
            cout << it->get_Plate() << "," << formatTime(it->getEntry_Time()) << ","
                 << (it->getExit_Time() == 0 ? "NONE" : formatTime(it->getExit_Time())) << ","
                 << it->getTotalHours() << ","
                 << "P" << it->getTotalCost() << "," << formatEntryDate(it->getEntry_Time()) << ","
                 << it->getBrand() << "," << it->getModel() << "," << it->getYear() << endl;
            cout << endl;
        } else {
            cout << "FIND " << plate << endl;
            cout << endl;
            cout << "CAR NOT FOUND" << endl;
            cout << endl;
        }
    }

// LIST
    void list() {
        cout << "LIST" << endl;
        cout << endl;
        for (const auto& entry : mainDatabase) {
            cout << entry.get_Plate() << "," << formatTime(entry.getEntry_Time()) << ","
                 << (entry.getExit_Time() == 0 ? "NONE" : formatTime(entry.getExit_Time())) << ","
                 << entry.getTotalHours() << ","
                 << "P" << entry.getTotalCost() << "," << formatEntryDate(entry.getEntry_Time()) << ","
                 << entry.getBrand() << "," << entry.getModel() << "," << entry.getYear() << endl;
        }
        cout << endl;
    }

// LOG
    void log() {
        cout << "LOG" << endl;
        cout << endl;
        for (const auto& entry : historyDatabase) {
            cout << entry.get_Plate() << "," << formatTime(entry.getEntry_Time()) << ","
                 << formatTime(entry.getExit_Time()) << ","
                 << entry.getTotalHours() << ","
                 << "P" << entry.getTotalCost() << "," << formatEntryDate(entry.getEntry_Time()) << ","
                 << entry.getBrand() << "," << entry.getModel() << "," << entry.getYear() << endl;
        }
        cout << endl;
    }

private:
    string formatTime(time_t timestamp) {
        char buffer[9];
        strftime(buffer, sizeof(buffer), "%T", localtime(&timestamp));
        return string(buffer);
    }

    string formatEntryDate(time_t timestamp) {
        char buffer[20];
        strftime(buffer, sizeof(buffer), "%a,%m/%d/%y", localtime(&timestamp));
        return string(buffer);
    }
};

// MAIN

int main() {
    ParkingSystem parkingSystem;
    string command;

    while (true) {
        cout << "> ";
        getline(cin, command);

        if (command.find("PARK") == 0) {
            istringstream iss(command);
            string cmd, plate, brand, model;
            int year;
            iss >> cmd >> plate >> brand >> model >> year;
            parkingSystem.park(plate, brand, model, year);
        } else if (command.find("EXIT") == 0) {
            istringstream iss(command);
            string cmd, plate;
            iss >> cmd >> plate;
            parkingSystem.exit(plate);
        } else if (command.find("FIND") == 0) {
            istringstream iss(command);
            string cmd, plate;
            iss >> cmd >> plate;
            parkingSystem.find(plate);
        } else if (command.find("LIST") == 0) {
            parkingSystem.list();
        } else if (command.find("LOG") == 0) {
            parkingSystem.log();
        } else if (command == "QUIT") {
            cout << "QUIT" << endl;
            break;
        } else {
            cout << "UNSUPPORTED COMMAND" << endl;
            cout << endl;
        }
    }

    return 0;
}
