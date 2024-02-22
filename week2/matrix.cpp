#include <iostream> 
#include <vector>  
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iomanip>
using namespace std; 

class Matrix{
private: 
    vector<vector<int>> mat;
    int rows, cols;

public: 
    Matrix() : rows(0), cols(0) {}
    int random(){
    int val = rand() % 100;
    return val;
}

    void print(){
        cout << endl;
        for (int i = 0; i < rows; ++i) { 
            cout << mat[i][0];   
            for (int j = 1; j < cols; ++j) {
                cout << " " << mat[i][j];
            }
            cout << endl;
        }
        cout << endl;
    }

    int get(int row, int col){
        int xdex = row - 1;
        int ydex = col - 1;
        if (0 < row && row <= rows && 0 < cols  && col <= cols) {
            cout << endl << "MATRIX [" << row << "][" << col << "] = " << mat[xdex][ydex] << endl;
            return mat[xdex][ydex];
        } else {
            cout << "\nUNSUPPORTED COMMAND" << endl;
        }
    }
        
    void set(int row, int col, int value) {
        int xdex = row - 1;
        int ydex = col - 1;
        if (value > 99){
            cout << "\nUNSUPPORTED COMMAND" << endl;
        }
        else if (row > 0 && row <= cols && col > 0 && col <= cols) {
            mat[xdex][ydex] = value;
            cout << endl << "MATRIX [" << row << "][" << col << "] = " << value << endl;
        } else {
            cout << "\nUNSUPPORTED COMMAND" << endl;
        }}

    void transpose(){
    vector<vector<int> > switched(cols, vector<int>(rows));
        for (int i = 1; i < rows; i++) {
            for (int j = 1; j < cols; j++) {
                switched[i][j] = mat[j][i];
            }
        }
        mat = switched;
        swap(rows, cols);

        cout << rows << "x" << cols << " MATRIX" << endl;
        }

    void swapRows(int row1, int row2) {
        int row1dex = row1 - 1;
        int row2dex = row2 - 1;
        if (row1 > 0 && row1 <= rows && row2 > 0 && row2 <= rows) {
            swap(mat[row1dex], mat[row2dex]);
            cout << "SWAPPED ROWS " << row1 << " AND " << row2 << endl;
        } else {
            cout << "\nUNSUPPORTED COMMAND" << endl;
        }
    }

    Matrix add(Matrix matrix1, Matrix matrix2){
        Matrix result;
        if (matrix1.rows != matrix2.rows){
            cout << "\nUNSUPPORTED COMMAND" << endl;
        } 
        for (int i = 1; i < rows; i++) {
            for (int j = 1; j < cols; j++){
                result.set(i + 1, j + 1, matrix1.get(i + 1, j + 1) + matrix2.get(i + 1, j + 1));
            }
    }
} 

    Matrix sub(Matrix matrix1, Matrix matrix2){
        Matrix result;
        if (matrix1.rows != matrix2.rows){
            cout << "\nUNSUPPORTED COMMAND" << endl;
        } 
        for (int i = 1; i < rows; i++) {
            for (int j = 1; j < cols; j++){
                result.set(i + 1, j + 1, matrix1.get(i + 1, j + 1) - matrix2.get(i + 1, j + 1));
            }
    }
} 
};