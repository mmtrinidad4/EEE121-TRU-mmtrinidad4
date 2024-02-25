#include "Matrix.h"
#include <iostream>
#include <iomanip>

void Matrix::print() {
    std::cout << "\n";
    for (int y = 0; y < num_rows; y += 1) {
        for (int x = 0; x < num_cols; x += 1) {
            std::cout << std::setw(2) << matrix_data[x][y] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

int Matrix::get(int row_index, int col_index) {
    return matrix_data[col_index - 1][row_index - 1];
}

void Matrix::set(int row_index, int col_index, int value) {
    matrix_data[col_index - 1][row_index - 1] = value;
}

void Matrix::transpose() {
    duplicate_matrix_data = matrix_data;
    matrix_data.clear();
    matrix_data.resize(num_cols, std::vector<int>(num_rows));
    for (int y = 0; y < num_cols; y += 1) {
        for (int x = 0; x < num_rows; x += 1) {
            matrix_data[y][x] = duplicate_matrix_data[x][y];
        }
    }
    int temp = num_cols;
    num_cols = num_rows;
    num_rows = temp;
}

void Matrix::swap_rows(int row1, int row2) {
    duplicate_matrix_data = matrix_data;
    for (int x = 0; x < num_cols; x += 1) {
        int temp = matrix_data[x][row1 - 1];
        matrix_data[x][row1 - 1] = matrix_data[x][row2 - 1];
        matrix_data[x][row2 - 1] = temp;
    }
}

Matrix Matrix::operator +(const Matrix& other) {
    Matrix result;
    result.num_rows = num_rows;
    result.num_cols = num_cols;
    result.matrix_data.resize(num_cols, std::vector<int>(num_rows));
    for (int y = 0; y < num_rows; y += 1) {
        for (int x = 0; x < num_cols; x += 1) {
            result.matrix_data[x][y] = matrix_data[x][y] + other.matrix_data[x][y];
        }
    }
    return result;
}

Matrix Matrix::operator -(const Matrix& other) {
    Matrix result;
    result.num_rows = num_rows;
    result.num_cols = num_cols;
    result.matrix_data.resize(num_cols, std::vector<int>(num_rows));
    for (int y = 0; y < num_rows; y += 1) {
        for (int x = 0; x < num_cols; x += 1) {
            result.matrix_data[x][y] = matrix_data[x][y] - other.matrix_data[x][y];
        }
    }
    return result;
}
