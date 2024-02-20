#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

class Matrix {
private:
    vector<vector<int>> matrixData;

public:
    Matrix() {}

    void initializeMatrix(int rows, int columns = -1) {
        matrixData.clear();
        matrixData.resize(rows);
        for (int i = 0; i < rows; ++i) {
            matrixData[i].resize((columns == -1) ? rows : columns);
            for (int j = 0; j < matrixData[i].size(); ++j) {
                matrixData[i][j] = rand() % 100;
            }
        }

        cout << '\n' << rows << "x" << ((columns == -1) ? rows : columns) << " MATRIX" << endl;
        cout << endl;
    }

    void printMatrix() const {
        cout << endl;
        for (const auto& row : matrixData) {
            for (const auto& element : row) {
                cout << setw(2) << element << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    void getElement(int row, int column) const {
        if (row > 0 && row <= matrixData.size() && column > 0 && column <= matrixData[0].size()) {
            cout << '\n' << "MATRIX[" << row << "][" << column << "] = " << matrixData[row - 1][column - 1] << endl;
        } else {
            cout << "\nUNSUPPORTED COMMAND" << endl;
        }
        
        cout << endl;
    }

    void setElement(int row, int column, int value) {
        cout << endl;
        if (row > 0 && row <= matrixData.size() && column > 0 && column <= matrixData[0].size()) {
            if (value >= 0 && value <= 99) { 
                matrixData[row - 1][column - 1] = value;
                cout << "MATRIX[" << row << "][" << column << "] = " << value << endl;
            } else {
                cout << endl;
                cout << "\nUNSUPPORTED COMMAND" << endl;
            }
        } else {
            cout << "\nUNSUPPORTED COMMAND" << endl;
        }
        cout << endl;
    }

    void transposeMatrix() {
        if (matrixData.empty()) {
            cout << endl;
            cout << "UNSUPPORTED COMMAND" << endl;
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

    void swapRows(int row1, int row2) {
        if (row1 > 0 && row1 <= matrixData.size() && row2 > 0 && row2 <= matrixData.size()) {

            row1--; 
            row2--;
            for (size_t i = 0; i < matrixData[0].size(); ++i) {
                swap(matrixData[row1][i], matrixData[row2][i]);
            }
            cout << endl;
            cout << "SWAPPED ROWS " << row1 + 1 << " AND " << row2 + 1 << endl;
        } else {
            cout << endl;
            cout << "\nUNSUPPORTED COMMAND" << endl;
        }
        cout << endl;
    }
};

int main() {
    srand(time(nullptr));

    Matrix matrixManipulator;
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
                cout << endl;
                cout << "UNSUPPORTED COMMAND" << endl;
                cout << endl;
            } else if (!(ss >> columns)) {
                matrixManipulator.initializeMatrix(rows);
            } else {
                matrixManipulator.initializeMatrix(rows, columns);
            }
        } else if (command == "PRINT") {
            matrixManipulator.printMatrix();
        } else if (command == "GET") {
            int row, column;
            if (ss >> row >> column) {
                matrixManipulator.getElement(row, column);
            } else {
                cout << "UNSUPPORTED COMMAND" << endl;
                cout << endl;
            }
        } else if (command == "SET") {
            int row, column, value;
            if (ss >> row >> column >> value) {
                matrixManipulator.setElement(row, column, value);
            } else {
                cout << endl;
                cout << "UNSUPPORTED COMMAND" << endl;
                cout << endl;
            }
        } else if (command == "TRANSPOSE") {
            string extra;
            if (ss >> extra){
                cout << endl;
                cout << "UNSUPPORTED COMMAND" << endl;
                cout << endl;
            } else {
                matrixManipulator.transposeMatrix();
            }
        } else if (command == "SWAP_ROWS") {
            int row1, row2;
            if (ss >> row1 >> row2) {
                matrixManipulator.swapRows(row1, row2);
            } else {
                cout << endl;
                cout << "UNSUPPORTED COMMAND" << endl;
                cout << endl;
            }
        } else if (command == "EXIT") {
            break;
        } else {
            cout << endl;
            cout << "UNSUPPORTED COMMAND" << endl;
            cout << endl;
        }
    }

    return 0;
}
