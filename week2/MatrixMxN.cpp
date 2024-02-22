#include "Matrix.h"

class MatrixMxN : public Matrix{
    private: 
    vector<vector<int>> mat;
    int rows, cols;
    string name;
    public: 
    MatrixMxN(): name(""), rows(0), cols(0) {}
    void init(string n, int x, int y){
        name = n;
        rows = x;
        cols = y;

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j){ 
                mat[i][j] = random();
            }
        }
        cout << '\n' << rows << "x" << cols << " MATRIX" << endl << endl;
    }
    string getname() {
    return this -> name;
    }};