#include "Matrix.h"

class MatrixNxN : public Matrix{
    private: 
    vector<vector<int>> mat;
    int rows, cols;
    string name;
    public: 
    MatrixNxN(): name(""), rows(0){}
    void init(string n, int x){
        name = n;
        rows = x;
        cols = x;

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