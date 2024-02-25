#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <string>

class Matrix {
public:
    std::string matrix_name;
    int num_rows;
    int num_cols;
    std::vector<std::vector<int>> matrix_data;
    std::vector<std::vector<int>> duplicate_matrix_data;

    void print();
    int get(int row_index, int col_index);
    void set(int row_index, int col_index, int value);
    void transpose();
    void swap_rows(int row1, int row2);
    Matrix operator +(const Matrix& other);
    Matrix operator -(const Matrix& other);
};

#endif
