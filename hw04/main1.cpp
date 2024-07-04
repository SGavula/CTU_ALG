#include <iostream>
#include <vector>

const int C = 5;  // Replace with the desired value of C
const int ROWS = 3;  // Replace with the desired number of rows
const int COLS = 4;  // Replace with the desired number of columns

int main() {
    // Create a vector of vectors for each of the C + 1 vectors
    std::vector<std::vector<int>> vectorOfVectors(C + 1, std::vector<int>(ROWS * COLS, -1));

    // Print the 2D vectors to verify the initialization
    for (int i = 0; i < C + 1; ++i) {
        std::cout << "Initialized 2D vector " << i << ":" << std::endl;
        for (int j = 0; j < ROWS; ++j) {
            for (int k = 0; k < COLS; ++k) {
                std::cout << vectorOfVectors[i][j * COLS + k] << " ";
            }
            std::cout << std::endl;
        }
    }

    return 0;
}