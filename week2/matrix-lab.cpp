#include <iostream>
#include <map>
#include <sstream>
#include <ctime>
#include "Matrix.h"
#include "MatrixNxN.h"
#include "MatrixMxN.h"

using namespace std;

int main() {
    string command;
    string argument;
    vector<string> syntax;
    int index;
    srand((unsigned)time(NULL));
    MatrixMxN MxN_matrix;
    MatrixNxN NxN_matrix;
    Matrix mtx;
    map<string, Matrix> matrices;

    while (true) {
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

        // INIT 
        if (syntax[0] == "INIT" && syntax[2] != "_" && syntax[4] == "_" && syntax[2] != "0" && syntax[3] != "0") {
            if (syntax[3] == "_") {
                NxN_matrix.matrix_name = syntax[1];
                NxN_matrix.num_rows = stoi(syntax[2]);
                NxN_matrix.initialize(NxN_matrix.num_rows);
                mtx = NxN_matrix;
            }
            else {
                MxN_matrix.matrix_name = syntax[1];
                MxN_matrix.num_rows = stoi(syntax[2]);
                MxN_matrix.num_cols = stoi(syntax[3]);
                MxN_matrix.initialize(MxN_matrix.num_rows, MxN_matrix.num_cols);
                mtx = MxN_matrix;
            }
            matrices[mtx.matrix_name] = mtx;
            cout << "\nMatrix " << mtx.matrix_name << " : " << mtx.num_rows << "x" << mtx.num_cols << "\n\n";
        }

        // PRINT        
        else if (syntax[0] == "PRINT" && syntax[2] == "_" && syntax[3] == "_" && syntax[4] == "_") {
            if (matrices.find(syntax[1]) == matrices.end()) {
                cout << "\nUNSUPPORTED COMMAND\n\n";
            }
            else {
                Matrix selected_matrix = matrices[syntax[1]];
                selected_matrix.print();
            }
        }

        // GET   
        else if (syntax[0] == "GET" && syntax[2] != "_" && syntax[3] != "_" && syntax[4] == "_") {
            if (matrices.find(syntax[1]) == matrices.end()) {
                cout << "\nUNSUPPORTED COMMAND\n\n";
            }
            else {
                Matrix selected_matrix = matrices[syntax[1]];
                int y_index = stoi(syntax[3]);
                int x_index = stoi(syntax[2]);
                if (x_index <= selected_matrix.num_cols && x_index > 0 && y_index <= selected_matrix.num_rows && y_index > 0) {
                    cout << "\n" << syntax[1] << "[" << y_index << "][" << x_index << "] = " << selected_matrix.get(y_index, x_index) << "\n\n";
                }
                else {
                    cout << "\nUNSUPPORTED COMMAND\n\n";
                }
            }
        }

        // SET       
        else if (syntax[0] == "SET" && syntax[2] != "_" && syntax[3] != "_" && syntax[4] != "_" && syntax[5] == "_") {
            if (matrices.find(syntax[1]) == matrices.end()) {
                cout << "\nUNSUPPORTED COMMAND\n\n";
            }
            else {
                Matrix selected_matrix = matrices[syntax[1]];
                int y_index = stoi(syntax[3]);
                int x_index = stoi(syntax[2]);
                int value = stoi(syntax[4]);
                if (x_index <= selected_matrix.num_cols && x_index > 0 && y_index <= selected_matrix.num_rows && y_index > 0 && value >= 0 && value < 100) {
                    selected_matrix.set(y_index, x_index, value);
                    matrices[selected_matrix.matrix_name] = selected_matrix;
                    cout << "\n" << syntax[1] << "[" << y_index << "][" << x_index << "] = " << selected_matrix.get(y_index, x_index) << "\n\n";
                }
                else {
                    cout << "\nUNSUPPORTED COMMAND\n\n";
                }
            }
        }

        // TRANSPOSE         
        else if (syntax[0] == "TRANSPOSE" && syntax[2] == "_" && syntax[3] == "_" && syntax[4] == "_") {
            if (matrices.find(syntax[1]) == matrices.end()) {
                cout << "\nUNSUPPORTED COMMAND\n\n";
            }
            else {
                Matrix selected_matrix = matrices[syntax[1]];
                selected_matrix.transpose();
                matrices[selected_matrix.matrix_name] = selected_matrix;
                cout << "\nMatrix " << syntax[1] << " : " << selected_matrix.num_rows << "x" << selected_matrix.num_cols << "\n\n";
            }
        }

        // SWAP ROWS        
        else if (syntax[0] == "SWAP_ROWS" && syntax[2] != "_" && syntax[3] != "_" && syntax[4] == "_") {
            if (matrices.find(syntax[1]) == matrices.end()) {
                cout << "\nUNSUPPORTED COMMAND\n\n";
            }
            else {
                Matrix selected_matrix = matrices[syntax[1]];
                int row_index1 = stoi(syntax[2]);
                int row_index2 = stoi(syntax[3]);
                if (row_index1 <= selected_matrix.num_rows && row_index1 > 0 && row_index2 <= selected_matrix.num_rows && row_index2 > 0) {
                    selected_matrix.swap_rows(row_index1, row_index2);
                    matrices[selected_matrix.matrix_name] = selected_matrix;
                    cout << "\nSWAPPED ROWS " << row_index1 << " and " << row_index2 << "\n\n";
                }
                else {
                    cout << "\nUNSUPPORTED COMMAND\n\n";
                }
            }
        }

        // + & - 
        else if (syntax[0] != "_" && syntax[2] != "_" && syntax[3] == "_" && syntax[4] == "_") {
            if (matrices.find(syntax[0]) != matrices.end() && matrices.find(syntax[2]) != matrices.end()) {
                Matrix matrix1 = matrices[syntax[0]];
                Matrix matrix2 = matrices[syntax[2]];
                Matrix result;
                if (matrix1.num_rows == matrix2.num_rows && matrix1.num_cols == matrix2.num_cols) {
                    if (syntax[1] == "+") {
                        result = matrix1 + matrix2;
                        matrices["RESULT"] = result;
                        cout << "\nMatrix Addition : " << result.num_rows << "x" << result.num_cols << "\n\n";
                    }
                    else if (syntax[1] == "-") {
                        result = matrix1 - matrix2;
                        matrices["RESULT"] = result;
                        cout << "\nMatrix Subtraction : " << result.num_rows << "x" << result.num_cols << "\n\n";
                    }
                    else {
                        cout << "\nUNSUPPORTED COMMAND\n\n";
                    }
                }
                else {
                    cout << "\nUNSUPPORTED COMMAND\n\n";
                }
            }
            else {
                cout << "\nUNSUPPORTED COMMAND\n\n";
            }
        }

        // EXIT 
        else if (syntax[0] == "EXIT" && syntax[1] == "_" && syntax[2] == "_" && syntax[3] == "_" && syntax[4] == "_") {
            break;
        }

        // UNSUPPORTED COMMAND
        else {
            cout << "\nUNSUPPORTED COMMAND\n\n";
        }
    }

    return 0;
}
