#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

/* Declarations of functions */
void print_matrix(vector<vector<int>>& matrix, int N);
vector<vector<int>> load_matrix(int N, string input);
void calculate_prefix_sum(vector<vector<int>>& matrix, vector<vector<int>>& prefix_sums_ones, vector<vector<int>>& prefix_sums_twos, int N);
int calculate_submatrix_sum(vector<vector<int>>& prefix_sums, int i, int j, int K);
int find_max_ones(vector<vector<int>>& matrix, int N, int K, int L, int S);

/* MAIN */
int main() {
    // Create variable string for storing the input
    string input;
    // Read first line
    getline(cin, input);
    // Extract values from first line to the variables
    istringstream iss(input);
    int N, K, L, S;
    iss >> N >> K >> L >> S;

    vector<vector<int>> matrix = load_matrix(N, input);

    int result = find_max_ones(matrix, N, K, L, S);
    cout << result << endl;

    return 0;
}


/* Definitions of functions */
void print_matrix(vector<vector<int>>& matrix, int N) {
    // Print the elements of the 2D vector
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

vector<vector<int>> load_matrix(int N, string input) {
    vector<vector<int>> matrix(N, vector<int>(N));

    for (int i = 0; i < N; ++i) {
        getline(cin, input);
        istringstream rowStream(input);
        for (int j = 0; j < N; ++j) {
            rowStream >> matrix[i][j];
        }
    }

    return matrix;
}

void calculate_prefix_sum(vector<vector<int>>& matrix, vector<vector<int>>& prefix_sums_ones, vector<vector<int>>& prefix_sums_twos, int N) {
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            prefix_sums_ones[i][j] = prefix_sums_ones[i - 1][j] + prefix_sums_ones[i][j - 1] - prefix_sums_ones[i - 1][j - 1] + (matrix[i - 1][j - 1] == 2 ? 0 : matrix[i - 1][j - 1]);
            prefix_sums_twos[i][j] = prefix_sums_twos[i - 1][j] + prefix_sums_twos[i][j - 1] - prefix_sums_twos[i - 1][j - 1] + (matrix[i - 1][j - 1] == 1 ? 0 : matrix[i - 1][j - 1]);
        }
    }
}

int calculate_submatrix_sum(vector<vector<int>>& prefix_sums, int i, int j, int K) {
    return prefix_sums[i + K][j + K] - prefix_sums[i][j + K] - prefix_sums[i + K][j] + prefix_sums[i][j];
}

int find_max_ones(vector<vector<int>>& matrix, int N, int K, int L, int S) {
    // Calculate prefix sums for twos and ones
    vector<vector<int>> prefix_sums_ones(N + 1, vector<int>(N + 1, 0));
    vector<vector<int>> prefix_sums_twos(N + 1, vector<int>(N + 1, 0));
    calculate_prefix_sum(matrix, prefix_sums_ones, prefix_sums_twos, N);
    
    // Iterate through the array and find the values that satisfied the condition
    int max_ones = 0;
    for (int i = 0; i <= N - K; ++i) {
        for (int j = 0; j <= N - K; ++j) {
            int total_twos = calculate_submatrix_sum(prefix_sums_twos, i + L, j + L, K - 2 * L);

            if (total_twos >= 2*S) {
                int total_ones = calculate_submatrix_sum(prefix_sums_ones, i, j, K);
                max_ones = max(max_ones, total_ones);
            }
        }
    }

    return max_ones;
}
