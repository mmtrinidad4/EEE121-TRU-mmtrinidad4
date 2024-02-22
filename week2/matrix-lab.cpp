#include "Matrix.h"
#include "MatrixMxN.h"
#include "MatrixNxN.h" // Make sure to include MatrixNxN.h if it's a separate header

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <variant> // Include the variant header

using namespace std;

int main() {
    srand(time(nullptr));
    Matrix matrix;
    MatrixNxN nmatrix;
    MatrixMxN mmatrix;
    string input;
    vector<std::variant<MatrixMxN, MatrixNxN>> objs; // Using std::variant to hold objects of different types
    
    while (true) {
        cout << endl << "> ";
        getline(cin, input);

        cout << input << endl;

        stringstream ss(input);
        string command;
        ss >> command;

        if (command == "INIT") {
            string name;
            int rows, columns, cols; // Declaring cols here
            if (!(ss >> name) || !(ss >> rows) || rows == 0 || !(ss >> columns) || columns == 0) {
                cout << "UNSUPPORTED COMMAND" << endl;
            }
            else {
                if (ss.peek() != EOF) {
                    cout << "Too many arguments for INIT command" << endl;
                    continue; // Skip to the next iteration of the loop
                }
                if (ss.fail()) {
                    cout << "Invalid argument for INIT command" << endl;
                    continue; // Skip to the next iteration of the loop
                }
                if (ss.bad()) {
                    cout << "Input stream failure" << endl;
                    break; // Exit the loops
                }

                if (ss >> cols) {
                    mmatrix.init(name, rows, cols);
                    objs.push_back(mmatrix);
                } else {
                    nmatrix.init(name, rows);
                    objs.push_back(nmatrix);
                }
            }
        }
        else {
            cout << "\nUNSUPPORTED COMMAND" << endl;
        }
        
        // Rest of your code
        for (auto& obj : objs) {
            if (holds_alternative<MatrixMxN>(obj)) {
                MatrixMxN& mmn = get<MatrixMxN>(obj);
                // Handle MatrixMxN operations
            }
            else if (holds_alternative<MatrixNxN>(obj)) {
                MatrixNxN& mnn = get<MatrixNxN>(obj);
                // Handle MatrixNxN operations
            }
        }
    }
    return 0;
}
