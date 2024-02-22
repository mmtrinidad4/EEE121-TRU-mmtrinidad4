#include "Matrix.h"

class MatrixMxN : public Matrix{
    private: 
    int rows, cols;
    string name;
    public: 
    MatrixMxN(): name(""), rows(0), cols(0) {}
    void init(string n, int x, int y){
        name = n;
        rows = x;
        cols = y;
    }
    string getname() {
    return this -> name;
    }};