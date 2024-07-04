#include <iostream>
#include <climits>
#include <vector>
#include <utility>
 
using namespace std;
 
// Declarations of functions
void printMatrix(vector<vector<int>>& matrix, int S);
bool areSatifactory(string str, string compString, int k);
void calculateRow(int i, vector<vector<int>>& matrix, string str, vector<string> inputStrings, int k, int S);
vector<vector<int>> createMatrix(int S, int K, vector<string> inputStrings);

/* MAIN */
int main() {
  // Read and store first line
  int S, K, M;
  cin >> S >> K >> M;
  // Declare a vector to store the input strings
  vector<string> inputStrings;

  // Read lines until there is no more input
  string line;
  while (getline(cin, line)) {
    // Add the line to the vector
    if(line.empty()) {
      continue;
    }
    inputStrings.push_back(line);
  }
  
  // for (const auto& str : inputStrings) {
  //   cout << str << endl;
  // }

  // Make matrix
  vector<vector<int>> matrix = createMatrix(S, K, inputStrings);
  // printMatrix(matrix, S);

  // Multiplication
  vector<long long unsigned int> resVector(S, 1);
  vector<long long unsigned int> newVector(S);

  for(int k = 0; k < (M-K); k++) {
    for(int i = 0; i < S; i++) {
      long long unsigned int cell = 0;
      for(int j = 0; j < S; j++) {
        cell = cell + (resVector[j] * matrix[j][i]);
      }
      newVector[i] = cell;
    }

    resVector = newVector;
  }

  long long unsigned int res = 0;
  for(int i = 0; i < S; i++) {
    res = res + resVector[i];
  }

  cout << res << endl;
  return 0;
}
 
// Definitions of functions
void printMatrix(vector<vector<int>>& matrix, int S) {
    for (int i = 0; i < S; ++i) {
        for (int j = 0; j < S; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

bool areSatifactory(string str, string compString, int k) {
  // cout << "Small k: " << k << endl;
  // String are same
  bool res = true;
  for(int i = 0; i < k; i++) {
    if(str[i] != compString[i+1]) {
      res = false;
      break;
    }
  }
  return res;
}

void calculateRow(int i, vector<vector<int>>& matrix, string str, vector<string> inputStrings, int k, int S) {
  for(int j = 0; j < S; j++) {
    bool res = areSatifactory(str, inputStrings[j], k);
    // cout << "(" << i << " " << j << ")" << endl;
    if(res == true) {
      matrix[j][i] = 1;
    } else {
      matrix[j][i] = 0;
    }
  }
}

vector<vector<int>> createMatrix(int S, int K, vector<string> inputStrings) {
  vector<vector<int>> matrix(S, vector<int>(S));

  for(int i = 0; i < S; i++) {
    calculateRow(i, matrix, inputStrings[i], inputStrings, K-1, S);
  }

  return matrix;
  
  // for (const auto& str : inputStrings) {
  //   calculateRow(matrix, str, inputStrings, K-1);
  // }
}
