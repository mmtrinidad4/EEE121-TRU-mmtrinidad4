#include <cstdlib>
#include <sstream> 
#include <iostream> 
#include <vector>
#include <ctime>
#include <algorithm> ///// for sorting
using namespace std; 

// void

void CSVprint(string plate, string inTime, string outTime, string hours, string fee, string day, string date, string brand, string model, string year){
    cout << plate << "," << inTime << "," << outTime << "," << hours << "," << fee << "," << day << "," << date << "," << brand << "," << model << "," << year << endl;
}

// conversion

string ConvertDate(string month, string day, string yr){
      
    string month_num;
    if(month == "Jan"){month_num = "01";} else if(month == "Feb"){month_num = "02";} else if(month == "Mar"){month_num = "03";}
    else if(month == "Apr"){month_num = "04";} else if(month == "May"){month_num = "05";} else if(month == "Jun"){month_num = "06";}
    else if(month == "Jul"){month_num = "07";} else if(month == "Aug"){month_num = "08";} else if(month == "Sep"){month_num = "09";}
    else if(month == "Oct"){month_num = "10";} else if(month == "Nov"){month_num = "11";} else if(month == "Dec"){month_num = "12";}
    

    string day_2digit;
    if(stoi(day) < 10){day_2digit = "0" + day;}
    else{day_2digit = day;}


    string yr_2digit = to_string(stoi(yr) - 2000);
        
    return month_num + "/" + day_2digit + "/" + yr_2digit;
}

///////// main

int main(){ 
    string command;
    string argmt;
    vector<string> syntax;
    int indx;
    string time_element;
    vector<string> time_string;
    vector<vector<string>> cars_parked;
    vector<vector<string>> car_log;
    bool bsort_called = false;
 
    while(true){
        int curSize = cars_parked.size();
        int logSize = car_log.size();
        string y = "";

        
        syntax.clear();
        cout << "> "; 
        getline(cin, command);
        cout << command << endl;
        stringstream parse(command);
        indx = 0;
        while(parse >> argmt){
            syntax.push_back(argmt);
            indx+=1;
        }
        for(indx; indx <= 5; indx+=1){
            syntax.push_back("_");
        }
        

    
        time_string.clear();
        time_t current_time = time(0);
        char* time_log = ctime(&current_time);
        stringstream split(time_log);
        while(split >> time_element){
            time_string.push_back(time_element);
        }

        // park //
        if(syntax[0] == "PARK" && syntax[1] != "_" && syntax[2] != "_" && syntax[3] != "_" && syntax[4] != "_" && syntax[5] == "_"){
            if(curSize <= 500){
                vector<string> car; 
                car.resize(10);        
                string entryTime = time_string[3]; 
                string day = time_string[0];
                string date = ConvertDate(time_string[1], time_string[2], time_string[4]);
                car = {syntax[1], entryTime, "NONE", "0", "P0", day, date, syntax[2], syntax[3], syntax[4]};
                cars_parked.push_back(car);
                cout << "\n";
            }
            else{
                cout << "\nUNSUPPORTED COMMAND\n\n";
            }
        }
        // list //
        else if(syntax[0] == "LIST" && syntax[1] == "_"){
            if(curSize != 0){
                cout << "\n";
                if (bsort_called) {
                    // ascending
                    sort(cars_parked.begin(), cars_parked.end(), [](const vector<string>& a, const vector<string>& b) {
                        return stoi(a[9]) < stoi(b[9]);
                    });
                    for(int x = 0; x < curSize; x+=1){
                        CSVprint(cars_parked[x][0], cars_parked[x][1], cars_parked[x][2], cars_parked[x][3], cars_parked[x][4], cars_parked[x][5], cars_parked[x][6], cars_parked[x][7], cars_parked[x][8], cars_parked[x][9]);
                    }
                    cout << "\n";
                }
                else {
                    for(int x = 0; x < curSize; x+=1){
                        CSVprint(cars_parked[x][0], cars_parked[x][1], cars_parked[x][2], cars_parked[x][3], cars_parked[x][4], cars_parked[x][5], cars_parked[x][6], cars_parked[x][7], cars_parked[x][8], cars_parked[x][9]);
                    }
                    cout << "\n";
                }
            }
            else{
                cout << "\nUNSUPPORTED COMMAND\n\n";
            }
        }   
        
        // find //
        else if(syntax[0] == "FIND" && syntax[1] != "_" && syntax[2] == "_"){
            cout << "\n";
            for(int x = 0; x < curSize; x+=1){
                if(cars_parked[x][0] == syntax[1]){
                    CSVprint(cars_parked[x][0], cars_parked[x][1], cars_parked[x][2], cars_parked[x][3], cars_parked[x][4], cars_parked[x][5], cars_parked[x][6], cars_parked[x][7], cars_parked[x][8], cars_parked[x][9]);
                    y = cars_parked[x][0];
                }
            }
            if(y != syntax[1]){
                cout << "CAR NOT FOUND\n";
            }
            cout << "\n";
        }
                // exit //
        else if(syntax[0] == "EXIT" && syntax[1] != "_" && syntax[2] == "_"){
            cout << endl;
            if(logSize <= 1000){
                int z = 0;
                string exitTime = time_string[3];
                string in_hr; string in_min;
                string out_hr; string out_min;
                int hours = 1; 
                int cost = 50;
                for(int x = 0; x < curSize; x+=1){
                    if(cars_parked[x][0] == syntax[1]){
                        y = cars_parked[x][0]; 
                        z = x;
                        cars_parked[x][2] = exitTime; 
                        in_hr += cars_parked[x][1][0]; in_hr += cars_parked[x][1][1]; in_min += cars_parked[x][1][3]; in_min += cars_parked[x][1][4];
                        out_hr += cars_parked[x][2][0]; out_hr += cars_parked[x][2][1]; out_min += cars_parked[x][2][3]; out_min += cars_parked[x][2][4];
                        hours += stoi(out_hr) - stoi(in_hr);
                        if((stoi(out_min) - stoi(in_min)) < 0){hours -= 1;}
                        if(hours > 3){cost += (hours-3)*20;}
                        cars_parked[x][3] = to_string(hours); 
                        cars_parked[x][4] = "P" + to_string(cost);
                        CSVprint(cars_parked[x][0], cars_parked[x][1], cars_parked[x][2], cars_parked[x][3], cars_parked[x][4], cars_parked[x][5], cars_parked[x][6], cars_parked[x][7], cars_parked[x][8], cars_parked[x][9]);
                        car_log.push_back(cars_parked[x]);
                    }
                }
                if(y != syntax[1]){
                    cout << "\nCAR NOT FOUND\n";
                }
                if(y == syntax[1]){
                    cars_parked.erase(cars_parked.begin()+z);
                }
                cout << "\n";
            }
            else{
                cout << "\nUNSUPPORTED COMMAND\n\n";
            }
        }


        // log //
        else if(syntax[0] == "LOG" && syntax[1] == "_"){
            if(logSize != 0){
                cout << "\n";
                for(int x = 0; x < logSize; x+=1){
                    CSVprint(car_log[x][0], car_log[x][1], car_log[x][2], car_log[x][3], car_log[x][4], car_log[x][5], car_log[x][6], car_log[x][7], car_log[x][8], car_log[x][9]);
                }
                cout << "\n";
            }
            else{
                cout << "\nUNSUPPORTED COMMAND\n\n";
            }
        }      
        
        // quit //
        else if(syntax[0] == "QUIT" && syntax[1] == "_"){
            break;
        }
        
        // bsort //
        // sort - ascending order
        else if (syntax[0] == "BSORT" && syntax[1] == "_"){
            sort(cars_parked.begin(), cars_parked.end(), [](const vector<string>& a, const vector<string>& b) {
                return stoi(a[9]) < stoi(b[9]);
            });
            cout << endl;
            for(int x = 0; x < curSize; x+=1){
                cout << "ITER-1 : ";
                CSVprint(cars_parked[x][0], cars_parked[x][1], cars_parked[x][2], cars_parked[x][3], cars_parked[x][4], cars_parked[x][5], cars_parked[x][6], cars_parked[x][7], cars_parked[x][8], cars_parked[x][9]);
            }
            cout << "\n";
            bsort_called = true;
        } // unsupported
        else{
            cout << "\nUNSUPPORTED COMMAND\n\n";
        }
    }

    return 0;
}

