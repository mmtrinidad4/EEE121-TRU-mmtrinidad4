#include "MatrixNxN.h"
#include <cstdlib>

void MatrixNxN::initialize(int rows) {
    num_cols = rows;
    matrix_data.resize(num_cols, std::vector<int>(rows));
    for (int y = 0; y < rows; y += 1) {
        for (int x = 0; x < num_cols; x += 1) {
            matrix_data[x][y] = rand() % 100;
        }
    }
}
