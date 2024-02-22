#include "Matrix.h"

class MatrixNxN : public Matrix{
    private: 
    int rows, cols;
    string name;
    public: 
    MatrixNxN(): name(""), rows(0){}
    void init(string n, int x){
        name = n;
        rows = x;
        cols = x;
        }
    string getname() {
    return this -> name;
    }};