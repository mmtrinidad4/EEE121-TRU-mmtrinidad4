#include <cstdlib>
#include <sstream>
#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

void printCSV(string plate, string inTime, string outTime, string hours, string fee, string day, string date, string brand, string model, string year) {
    cout << plate << "," << inTime << "," << outTime << "," << hours << "," << fee << "," << day << "," << date << "," << brand << "," << model << "," << year << endl;
}

string convertDate(string month, string day, string yr) {
    string monthNum;
    if (month == "Jan") monthNum = "01";
    else if (month == "Feb") monthNum = "02";
    else if (month == "Mar") monthNum = "03";
    else if (month == "Apr") monthNum = "04";
    else if (month == "May") monthNum = "05";
    else if (month == "Jun") monthNum = "06";
    else if (month == "Jul") monthNum = "07";
    else if (month == "Aug") monthNum = "08";
    else if (month == "Sep") monthNum = "09";
    else if (month == "Oct") monthNum = "10";
    else if (month == "Nov") monthNum = "11";
    else if (month == "Dec") monthNum = "12";

    string day2Digit;
    if (stoi(day) < 10) day2Digit = "0" + day;
    else day2Digit = day;

    string yr2Digit = to_string(stoi(yr) - 2000);

    return monthNum + "/" + day2Digit + "/" + yr2Digit;
}

int main() {
    string command;
    string argument;
    vector<string> syntax;
    int index;
    string timeElement;
    vector<string> timeString;
    vector<vector<string>> carsParked;
    vector<vector<string>> carLog;

    while (true) {
        int currentSize = carsParked.size();
        int logSize = carLog.size();
        string y = "";

        syntax.clear();
        cout << "> ";
        getline(cin, command);
        cout << command << endl;
        stringstream parse(command);
        index = 0;
        while (parse >> argument) {
            syntax.push_back(argument);
            index += 1;
        }
        for (index; index <= 5; index += 1) {
            syntax.push_back("_");
        }

        timeString.clear();
        time_t currentTime = time(0);
        char* timeLog = ctime(&currentTime);
        stringstream split(timeLog);
        while (split >> timeElement) {
            timeString.push_back(timeElement);
        }

        if (syntax[0] == "PARK" && syntax[1] != "_" && syntax[2] != "_" && syntax[3] != "_" && syntax[4] != "_" && syntax[5] == "_") {
            if (currentSize <= 500) {
                vector<string> car;
                car.resize(10);
                string entryTime = timeString[3];
                string day = timeString[0];
                string date = convertDate(timeString[1], timeString[2], timeString[4]);
                car = { syntax[1], entryTime, "NONE", "0", "P0", day, date, syntax[2], syntax[3], syntax[4] };
                carsParked.push_back(car);
                cout << "\n";
            } else {
                cout << "\nUNSUPPORTED COMMAND\n\n";
            }
        } else if (syntax[0] == "LIST" && syntax[1] == "_") {
            if (currentSize != 0) {
                cout << "\n";
                for (int x = 0; x < currentSize; x += 1) {
                    printCSV(carsParked[x][0], carsParked[x][1], carsParked[x][2], carsParked[x][3], carsParked[x][4], carsParked[x][5], carsParked[x][6], carsParked[x][7], carsParked[x][8], carsParked[x][9]);
                }
                cout << "\n";
            } else {
                cout << "\nUNSUPPORTED COMMAND\n\n";
            }
        } else if (syntax[0] == "FIND" && syntax[1] != "_" && syntax[2] == "_") {
            cout << "\n";
            for (int x = 0; x < currentSize; x += 1) {
                if (carsParked[x][0] == syntax[1]) {
                    printCSV(carsParked[x][0], carsParked[x][1], carsParked[x][2], carsParked[x][3], carsParked[x][4], carsParked[x][5], carsParked[x][6], carsParked[x][7], carsParked[x][8], carsParked[x][9]);
                    y = carsParked[x][0];
                }
            }
            if (y != syntax[1]) {
                cout << "CAR NOT FOUND\n";
            }
            cout << "\n";
        } else if (syntax[0] == "EXIT" && syntax[1] != "_" && syntax[2] == "_") {
            cout << endl;
            if (logSize <= 1000) {
                int z = 0;
                string exitTime = timeString[3];
                string inHr, inMin, outHr, outMin;
                int hours = 1;
                int cost = 50;
                for (int x = 0; x < currentSize; x += 1) {
                    if (carsParked[x][0] == syntax[1]) {
                        y = carsParked[x][0];
                        z = x;
                        carsParked[x][2] = exitTime;
                        inHr += carsParked[x][1][0];
                        inHr += carsParked[x][1][1];
                        inMin += carsParked[x][1][3];
                        inMin += carsParked[x][1][4];
                        outHr += carsParked[x][2][0];
                        outHr += carsParked[x][2][1];
                        outMin += carsParked[x][2][3];
                        outMin += carsParked[x][2][4];
                        hours += stoi(outHr) - stoi(inHr);
                        if ((stoi(outMin) - stoi(inMin)) < 0) hours -= 1;
                        if (hours > 3) cost += (hours - 3) * 20;
                        carsParked[x][3] = to_string(hours);
                        carsParked[x][4] = "P" + to_string(cost);
                        carLog.push_back(carsParked[x]);
                    }
                }
                if (y != syntax[1]) {
                    cout << "\nCAR NOT FOUND\n";
                }
                if (y == syntax[1]) {
                    printCSV(carsParked[z][0], carsParked[z][1], carsParked[z][2], carsParked[z][3], carsParked[z][4], carsParked[z][5], carsParked[z][6], carsParked[z][7], carsParked[z][8], carsParked[z][9]);
                    carsParked.erase(carsParked.begin() + z);
                }
                cout << "\n";
            } else {
                cout << "\nUNSUPPORTED COMMAND\n\n";
            }
        } else if (syntax[0] == "LOG" && syntax[1] == "_") {
            if (logSize != 0) {
                cout << "\n";
                for (int x = 0; x < logSize; x += 1) {
                    printCSV(carLog[x][0], carLog[x][1], carLog[x][2], carLog[x][3], carLog[x][4], carLog[x][5], carLog[x][6], carLog[x][7], carLog[x][8], carLog[x][9]);
                }
                cout << "\n";
            } else {
                cout << "\nUNSUPPORTED COMMAND\n\n";
            }
        } else if (syntax[0] == "QUIT" && syntax[1] == "_") {
            break;
        } else {
            cout << "\nUNSUPPORTED COMMAND\n\n";
        }
    }

    return 0;
}
