#include "Matrix.h"
#include "MatrixMxN.h"
#include "MatrixNxN.h"

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <variant> 

using namespace std;

int main() {
    srand(time(nullptr));
    Matrix matrix;
    MatrixNxN nmatrix;
    MatrixMxN mmatrix;
    string input;
    vector<std::variant<MatrixMxN, MatrixNxN>> objs; 
    
    while (true) {
        cout << endl << "> ";
        getline(cin, input);

        cout << input << endl;

        stringstream ss(input);
        string command;
        ss >> command;

        if (command == "INIT") {
            string name;
            int rows, columns, cols;
            if (!(ss >> name) || !(ss >> rows) || rows == 0 || !(ss >> columns) || columns == 0) {
                cout << "UNSUPPORTED COMMAND" << endl;
            }
            else {
                if (ss.peek() != EOF) {
                    cout << "Too many arguments for INIT command" << endl;
                    continue; 
                }
                if (ss.fail()) {
                    cout << "Invalid argument for INIT command" << endl;
                    continue; 
                }
                if (ss.bad()) {
                    cout << "Input stream failure" << endl;
                    break; 
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
        
        
        for (auto& obj : objs) {
            if (holds_alternative<MatrixMxN>(obj)) {
                MatrixMxN& mmn = get<MatrixMxN>(obj);
               
            }
            else if (holds_alternative<MatrixNxN>(obj)) {
                MatrixNxN& mnn = get<MatrixNxN>(obj);
             
            }
        }
    }
    return 0;
}
