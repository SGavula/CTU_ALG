#include <iostream>
#include <climits>
#include <vector>
#include <utility>
 
using namespace std;
 
// Declarations of functions
void printGrid(vector<vector<int>>& grid, int M, int N) {
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}
 
void printDPTable(vector<vector<pair<int, int>>> table, int M, int N) {
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << "("<< table[i][j].first << ", " << table[i][j].second << ")" << " ";
        }
        cout << endl;
    }
}
 
pair<int, int> maxPair(pair<int, int> firstPair, pair<int, int> secondPair) {
  if(firstPair.first > secondPair.first) {
    return firstPair;
  }
 
  if(firstPair.first < secondPair.first) {
    return secondPair;
  }
 
  if(firstPair.second < secondPair.second) {
    return firstPair;
  }
 
  return secondPair;
}
 
vector<vector<int>> loadGrid(int M ,int N) {
    vector<vector<int>> grid(M, vector<int>(N));
     
    for (int i = 0; i < M; ++i) {
      for (int j = 0; j < N; ++j) {
        int value = 0;
        cin >> value;
        // cout << value << endl;
        if(value != 0) {
          grid[i][j] = -1;
          // Top
          if((i-1) >= 0 && grid[i-1][j] != -1) {
            grid[i-1][j] = grid[i-1][j] + value; 
          }
          // Bottom
          if((i+1) < M && grid[i+1][j] != -1) {
            grid[i+1][j] = grid[i+1][j] + value; 
          }
          // Left
          if((j-1) >= 0 && grid[i][j-1] != -1) {
            grid[i][j-1] = grid[i][j-1] + value; 
          }
          // Right
          if((j+1) < N && grid[i][j+1] != -1) {
            grid[i][j+1] = grid[i][j+1] + value; 
          }
        }
      }
    }
    return grid;
}
 
/* MAIN */
int main() {
  // Read and store first line
  int M, N;
  cin >> M >> N;

  bool firstEmpty = true;
  vector<vector<int>> grid = loadGrid(M, N);
  for(int i = 0; i < N; i++) {
    if(grid[0][i] != 0) {
      firstEmpty = false;
    }
  }
  // cout << "First empty: " << firstEmpty << endl;
  // printGrid(grid, M, N);
 
  // Left table
  vector<vector<pair<int, int>>> leftDPTable(M, vector<pair<int, int>>(N));
  // Right table
  vector<vector<pair<int, int>>> rightDPTable(M, vector<pair<int, int>>(N));
     
  for (int i = 0; i < M; ++i) {
    for (int j = 0; j < N; ++j) {
      int k = (N-1) - j;
 
      if(grid[i][j] == -1) {
        leftDPTable[i][j].first = -1;
      }
 
      if(grid[i][k] == -1) {
        rightDPTable[i][k].first = -1;
      }
 
      if(i == 0 && firstEmpty == true) {
        leftDPTable[i][j].second = 1;
        rightDPTable[i][j].second = 1;
        continue;
      }
 
      // First row
      if(i == 0) {
        if(grid[i][j] != -1) {
          leftDPTable[i][j].first = leftDPTable[i][j].first + grid[i][j];

          // First column
          if(j == 0 && grid[i][j] != 0) {
            leftDPTable[i][j].second = 1;
          }
          if(j-1 >= 0 && grid[i][j-1] != -1) {
            leftDPTable[i][j].first = leftDPTable[i][j].first + leftDPTable[i][j-1].first;
            if(leftDPTable[i][j-1].first == 0 && leftDPTable[i][j-1].second == 0 && grid[i][j] == 0) {
              leftDPTable[i][j].second = 0;
            } else {
              leftDPTable[i][j].second = leftDPTable[i][j-1].second + 1;
            }
          }else {
            if(grid[i][j] != 0) {
              leftDPTable[i][j].second = 1;
            }
          }
        }
 
        if(grid[i][k] != -1) {
          rightDPTable[i][k].first = rightDPTable[i][k].first + grid[i][k];

          // Last column
          if(k == N-1 && grid[i][k] != 0) {
            rightDPTable[i][k].second = 1;
          }
 
          if(k+1 < N && grid[i][k+1] != -1) {
            rightDPTable[i][k].first = rightDPTable[i][k].first + rightDPTable[i][k+1].first;
            if(rightDPTable[i][k+1].first == 0 && rightDPTable[i][k+1].second == 0 && grid[i][k] == 0) {
              rightDPTable[i][k].second = 0;
            } else {
              rightDPTable[i][k].second = rightDPTable[i][k+1].second + 1;
            }
          }else {
            if(grid[i][k] != 0) {
              rightDPTable[i][k].second = 1;
            }
          }
        }
      } else {
        // Left table
        if(grid[i][j] != -1) {
          pair<int, int> maxPrevValue;
          // First column
          if(j == 0) {
            maxPrevValue = maxPair(leftDPTable[i-1][j], rightDPTable[i-1][j]);
            if(maxPrevValue.first == -1) {
              leftDPTable[i][j].first = grid[i][j];
              leftDPTable[i][j].second = 1;
            }else {
              leftDPTable[i][j].first = maxPrevValue.first + grid[i][j];  
              leftDPTable[i][j].second = maxPrevValue.second + 1;  
            }
          }else {
            maxPrevValue = maxPair(maxPair(leftDPTable[i-1][j], rightDPTable[i-1][j]), leftDPTable[i][j-1]);
            if(maxPrevValue.first == -1) {
              leftDPTable[i][j].first = grid[i][j];
            }else {
              leftDPTable[i][j].first = maxPrevValue.first + grid[i][j];
            }
            leftDPTable[i][j].second = maxPrevValue.second + 1;
          }
        }
 
        // Right table
        if(grid[i][k] != -1) {
          pair<int, int> maxPrevValueRight;
          // First column
          if(k == N-1) {
            maxPrevValueRight = maxPair(leftDPTable[i-1][k], rightDPTable[i-1][k]);
            if(maxPrevValueRight.first == -1) {
              rightDPTable[i][k].first = grid[i][k];
              rightDPTable[i][k].second = 1;
            }else {
              rightDPTable[i][k].first = maxPrevValueRight.first + grid[i][k];  
              rightDPTable[i][k].second = maxPrevValueRight.second + 1;  
            }
            continue;
          }
 
          maxPrevValueRight = maxPair(maxPair(leftDPTable[i-1][k], rightDPTable[i-1][k]), rightDPTable[i][k+1]);
          if(maxPrevValueRight.first == -1) {
            rightDPTable[i][k].first = grid[i][k];
          }else {
            rightDPTable[i][k].first = maxPrevValueRight.first + grid[i][k];
          }
          rightDPTable[i][k].second = maxPrevValueRight.second + 1;
        }
      }
    }
  }
 
  // cout << endl;
  // cout << endl;
  // cout << endl;
  // printDPTable(leftDPTable, M, N);
 
  // cout << endl;
  // cout << endl;
  // cout << endl;
  // printDPTable(rightDPTable, M, N);
 
  // Finding the maximum value from the last row of the left table
  int lastRow = M - 1;
  pair<int, int> maxValue = leftDPTable[lastRow][0]; // Initialize with the first element in the last row
 
  for (int j = 1; j < N; ++j) {
      pair<int, int> currentValue = leftDPTable[lastRow][j];
      if (currentValue.first > maxValue.first) {
        maxValue = currentValue;
      }
      if(currentValue.first == maxValue.first) {
        if(currentValue.second < maxValue.second) {
          maxValue = currentValue;
        }
      }
  }
 
  for (int j = 0; j < N; ++j) {
      pair<int, int> currentValue = rightDPTable[lastRow][j];
      if (currentValue.first > maxValue.first) {
        maxValue = currentValue;
      }
      if(currentValue.first == maxValue.first) {
        if(currentValue.second < maxValue.second) {
          maxValue = currentValue;
        }
      }
  }
 
  cout << maxValue.first << " " << maxValue.second << endl;
  return 0;
}
 
// Definitions of functions