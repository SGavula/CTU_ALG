#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

struct Node {
    int x;
    int y;
    int dist;
    int switchValue;
};

void printGrid(vector<vector<int>>& grid, int M, int N) {
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

void printVisitedPlaces(vector<vector<int>>& visitedPlaces, int C, int M, int N) {
    for (int i = 0; i < C + 1; ++i) {
        cout << "Initialized 2D vector " << i << ":" << endl;
        for (int j = 0; j < M; ++j) {
            for (int k = 0; k < N; ++k) {
                cout << visitedPlaces[i][j * N + k] << " ";
            }
            cout << endl;
        }
    }
}

vector<vector<int>> loadGrid(int M ,int N) {
    vector<vector<int>> grid(M, vector<int>(N));
    
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> grid[i][j];
        }
    }
    
    return grid;
}

bool isValid(int x, int y, int M, int N) {
    return x >= 0 && x < M && y >= 0 && y < N;
}

int main() {
    int dx[] = {0, -1, 0, 1};
    int dy[] = {1, 0, -1, 0};
    int switchValue = 0;
    
    int M, N, C;
    cin >> M >> N >> C;

    vector<vector<int>> grid = loadGrid(M, N);
    queue<Node> q;
    // Create an array of sets, each of size C + 1
    vector<vector<int>> visitedPlaces(C + 1, vector<int>(M * N, -1));
    
    struct Node start;
    start.x = (M-1);
    start.y = 0;
    start.dist = 0;
    start.switchValue = 0;

    q.push(start);

    while(!q.empty()) {
        Node current = q.front();
        q.pop();

        if (current.x == 0 && current.y == (N-1)) {
            cout << current.dist << endl;
            return 0;
        }

        for (int i = 0; i < 4; ++i) {
            int newX = current.x + dx[i];
            int newY = current.y + dy[i];
            if(isValid(newX, newY, M, N) == false) {
                continue;
            }

            if(grid[newX][newY] <= 0 || grid[newX][newY] == abs(current.switchValue)) {
                if(visitedPlaces[abs(current.switchValue)][newX * N + newY] == -1) {
                    // Empty place for visit
                    struct Node newNode;
                    newNode.x = newX;
                    newNode.y = newY;
                    newNode.dist = current.dist + 1;
                    newNode.switchValue = current.switchValue;
                    
                    // Visited switch
                    if(grid[newX][newY] < 0) {
                        // Visited the switch of same color
                        if(grid[newX][newY] != current.switchValue) {
                            newNode.switchValue = grid[newX][newY];
                            visitedPlaces[abs(current.switchValue)][newNode.x * N + newNode.y] = newNode.dist;
                        }
                    }

                    q.push(newNode);
                    if(visitedPlaces[abs(newNode.switchValue)][newNode.x * N + newNode.y] == -1) {
                        visitedPlaces[abs(newNode.switchValue)][newNode.x * N + newNode.y] = newNode.dist;
                    } 
                }
            }
        }
    }
    return 0;
}