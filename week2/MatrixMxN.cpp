#include "MatrixMxN.h"
#include <cstdlib>

void MatrixMxN::initialize(int rows, int cols) {
    matrix_data.resize(cols, std::vector<int>(rows));
    for (int y = 0; y < rows; y += 1) {
        for (int x = 0; x < cols; x += 1) {
            matrix_data[x][y] = rand() % 100;
        }
    }
}
