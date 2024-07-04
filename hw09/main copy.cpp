// Source of AVL tree implementation in C++: https://www.programiz.com/dsa/avl-tree

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

void makeLeftDPTable(vector<vector<pair<int, int>>>& leftDPTable, vector<vector<pair<int, int>>> rightDPTable, vector<vector<int>> grid, int i, int j) {
  if(grid[i][j] == -1) {
    leftDPTable[i][j].first = -1;
    return;
  }

  // First row
  if(i == 0) {
    leftDPTable[i][j].first = leftDPTable[i][j].first + grid[i][j];
    
    // First column
    if(grid[i][j] == 0 && j == 0) {
      leftDPTable[i][j].second = 0;
      return;
    }
    
    // Handle border
    if(j-1 < 0 || grid[i][j-1] == -1) {
      // cout << grid[i][j] << endl;
      leftDPTable[i][j].second = 1;
      return;
    }

    if(grid[i][j] == 0 && leftDPTable[i][j-1].second == 0) {
      leftDPTable[i][j].second = 0;
      return;
    }

    leftDPTable[i][j].first = leftDPTable[i][j].first + leftDPTable[i][j-1].first;
    leftDPTable[i][j].second = leftDPTable[i][j-1].second + 1;
  } else {
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
      return;
    }

    maxPrevValue = maxPair(maxPair(leftDPTable[i-1][j], rightDPTable[i-1][j]), leftDPTable[i][j-1]);
    if(maxPrevValue.first == -1) {
      leftDPTable[i][j].first = grid[i][j];
    }else {
      leftDPTable[i][j].first = maxPrevValue.first + grid[i][j];
    }
    leftDPTable[i][j].second = maxPrevValue.second + 1;
  }
}

void makeRightDPTable(vector<vector<pair<int, int>>>& rightDPTable, vector<vector<pair<int, int>>> leftDPTable, vector<vector<int>> grid, int i, int j, int N) {
  j = (N-1) - j;

  // cout << "J: " << j << endl;

  if(grid[i][j] == -1) {
    rightDPTable[i][j].first = -1;
    return;
  }

  //First row
  if(i == 0) {
    rightDPTable[i][j].first = rightDPTable[i][j].first + grid[i][j];

    // Last column
    if(grid[i][j] == 0 && j == N-1) {
      rightDPTable[i][j].second = 0;
      return;
    }

    // Handle border
    if(j+1 >= N || grid[i][j+1] == -1) {
      rightDPTable[i][j].second = 1;
      return;
    }

    if(grid[i][j] == 0 && rightDPTable[i][j+1].second == 0) {
      // cout << i << " " << j << endl;
      rightDPTable[i][j].second = 0;
      return;
    }

    rightDPTable[i][j].first = rightDPTable[i][j].first + rightDPTable[i][j+1].first;
    rightDPTable[i][j].second = rightDPTable[i][j+1].second + 1;
  }else {
    pair<int, int> maxPrevValue;
    // Last column
    if(j == N-1) {
      maxPrevValue = maxPair(leftDPTable[i-1][j], rightDPTable[i-1][j]);
      if(maxPrevValue.first == -1) {
        rightDPTable[i][j].first = grid[i][j];
        rightDPTable[i][j].second = 1;
      }else {
        rightDPTable[i][j].first = maxPrevValue.first + grid[i][j];  
        rightDPTable[i][j].second = maxPrevValue.second + 1;  
      }
      // cout << "Max prev value: " << maxPrevValue << endl;
      return;
    }

    maxPrevValue = maxPair(maxPair(leftDPTable[i-1][j], rightDPTable[i-1][j]), rightDPTable[i][j+1]);
    rightDPTable[i][j].first = maxPrevValue.first + grid[i][j];
    rightDPTable[i][j].second = maxPrevValue.second + 1;
  }
}

vector<vector<int>> loadGrid(int M ,int N) {
    vector<vector<int>> grid(M, vector<int>(N));
    
    for (int i = 0; i < M; ++i) {
      for (int j = 0; j < N; ++j) {
        int value = 0;
        cin >> value;
        // cout << value << endl;
        if(value != 0) {
          // cout << i << " " << j << endl;
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
  int numOfLines = 0;
  // Read and store first line
  int M, N;
  cin >> M;
  cin >> N;

  vector<vector<int>> grid = loadGrid(M, N);
  printGrid(grid, M, N);

  // Left table
  vector<vector<pair<int, int>>> leftDPTable(M, vector<pair<int, int>>(N));
  // Right table
  vector<vector<pair<int, int>>> rightDPTable(M, vector<pair<int, int>>(N));
    
  for (int i = 0; i < M; ++i) {
    for (int j = 0; j < N; ++j) {
      makeLeftDPTable(leftDPTable, rightDPTable, grid, i, j);
      makeRightDPTable(rightDPTable, leftDPTable, grid, i, j, N);
    }
  }

  cout << endl;
  cout << endl;
  cout << endl;
  printDPTable(leftDPTable, M, N);

  cout << endl;
  cout << endl;
  cout << endl;
  printDPTable(rightDPTable, M, N);

Finding the maximum value from the last row of the left table
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
}

// Definitions of functions

