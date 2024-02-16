#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

// initializing matrix
void initializeMatrix(vector<vector<int>>& matrixData, int rows, int columns = -1) {
    matrixData.clear();
    matrixData.resize(rows);
    for (int i = 0; i < rows; ++i) {
        matrixData[i].resize((columns == -1) ? rows : columns);
        for (int j = 0; j < matrixData[i].size(); ++j) {
            matrixData[i][j] = rand() % 100; // Ensures values are between 0 and 99
        }
    }

    cout << '\n' << rows << "x" << ((columns == -1) ? rows : columns) << " MATRIX" << endl;
    cout << endl;
}

// print matrix
void printMatrix(const vector<vector<int>>& matrixData) {
    cout << endl;
    for (const auto& row : matrixData) {
        for (const auto& element : row) {
            cout << setw(2) << element << " ";
        }
        cout << endl;
    }
    cout << endl;
}


// get element
void getElement(const vector<vector<int>>& matrixData, int row, int column) {
    if (row > 0 && row <= matrixData.size() && column > 0 && column <= matrixData[0].size()) {
        cout << '\n' << "MATRIX [" << row << "][" << column << "] = " << matrixData[row - 1][column - 1] << endl;
    } else {
        cout << "\nUNSUPPORTED COMMAND" << endl;
    }
    
    cout << endl;
}

// set
void setElement(vector<vector<int>>& matrixData, int row, int column, int value) {
    cout << endl;
    if (row > 0 && row <= matrixData.size() && column > 0 && column <= matrixData[0].size()) {
        if (value >= 0 && value <= 99) { // Ensure value is between 0 and 99
            matrixData[row - 1][column - 1] = value;
            cout << "MATRIX [" << row << "][" << column << "] = " << value << endl;
        } else {
            cout << "\nUNSUPPORTED COMMAND" << endl;
        }
    } else {
        cout << "\nUNSUPPORTED COMMAND" << endl;
    }
    cout << endl;
}

// transpose 
void transposeMatrix(vector<vector<int>>& matrixData) {
    if (matrixData.empty()) {
        cout << "Matrix is empty" << endl;
        return;
    }

    size_t rowCount = matrixData.size();
    size_t columnCount = matrixData[0].size();
    vector<vector<int>> transposed(columnCount, vector<int>(rowCount));
    for (size_t i = 0; i < rowCount; ++i) {
        for (size_t j = 0; j < columnCount; ++j) {
            transposed[j][i] = matrixData[i][j];
        }
    }
    cout << endl;
    matrixData = transposed;
    cout << columnCount << "x" << rowCount << " MATRIX" << endl;
    cout << endl;
}


void swapRows(vector<vector<int>>& matrixData, int row1, int row2) {
    if (row1 > 0 && row1 <= matrixData.size() && row2 > 0 && row2 <= matrixData.size()) {
        // Swap rows
        row1--; // Adjust indices to match vector indexing
        row2--;
        for (size_t i = 0; i < matrixData[0].size(); ++i) {
            swap(matrixData[row1][i], matrixData[row2][i]);
        }
        cout << endl;
        cout << "SWAPPED ROWS " << row1 + 1 << " AND " << row2 + 1 << endl; // Adjust back to 1-based indexing
    } else {
        cout << "\nUNSUPPORTED COMMAND" << endl;
    }
    cout << endl;
}


// MAIN 

int main() {
    srand(time(nullptr));

    vector<vector<int>> matrixData;
    string input;
    while (true) {
        cout << "> ";
        getline(cin, input);

        cout << input << endl;

        stringstream ss(input);
        string command;
        ss >> command;

        if (command == "INIT") {
            int rows, columns;
            if (!(ss >> rows)) {
                cout << "UNSUPPORTED COMMAND" << endl;
            } else if (!(ss >> columns)) {
                initializeMatrix(matrixData, rows);
            } else {
                initializeMatrix(matrixData, rows, columns);
            }
        } else if (command == "PRINT") {
            printMatrix(matrixData);
        } else if (command == "GET") {
            int row, column;
            if (ss >> row >> column) {
                getElement(matrixData, row, column);
            } else {
                cout << "UNSUPPORTED COMMAND" << endl;
            }
        } else if (command == "SET") {
            int row, column, value;
            if (ss >> row >> column >> value) {
                setElement(matrixData, row, column, value);
            } else {
                cout << "UNSUPPORTED COMMAND" << endl;
            }
        } else if (command == "TRANSPOSE") {
            string extra;
            if (ss >> extra){
                cout << "UNSUPPORTED COMMAND" << endl;
            } else {
                transposeMatrix(matrixData);
            }
        } else if (command == "SWAP_ROWS") {
            int row1, row2;
            if (ss >> row1 >> row2) {
                swapRows(matrixData, row1, row2);
            } else {
                cout << "UNSUPPORTED COMMAND" << endl;
            }
        } else if (command == "EXIT") {
            break;
        } else {
            cout << "UNSUPPORTED COMMAND" << endl;
        }
    }

    return 0;
}
