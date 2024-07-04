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

    bool operator<(const Node& other) const {
        return dist > other.dist; // Note: We use > for min heap
    }
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
    priority_queue<Node> q_switches;
    // Create an array of sets, each of size C + 1
    vector<vector<int>> visitedPlaces(C + 1, vector<int>(M * N, -1));
    // Print first row
    // cout << M << " " << N << " " << C << endl;
    // Print grid
    // printGrid(grid, M, N);
    
    struct Node start;
    start.x = (M-1);
    start.y = 0;
    start.dist = 0;

    q_switches.push(start);
    visitedPlaces[abs(switchValue)][start.x * N + start.y] = start.dist;
    // printVisitedPlaces(visitedPlaces, C, M, N);
    
    while(!q_switches.empty()) {
        start = q_switches.top();
        q_switches.pop();
        // cout << "Start Node: " << start.dist  << endl;
        switchValue = grid[start.x][start.y];
        visitedPlaces[abs(switchValue)][start.x * N + start.y] = start.dist;
        q.push(start);
        while(!q.empty()) {
            // cout << "Hello" << endl;
            Node current = q.front();
            q.pop();

            // cout << "Length of queue: " << q.size() << endl;
            // cout << "Current node: "<< current.x << " " << current.y << " " << current.dist << " " << grid[current.x][current.y] << endl;
            if (current.x == 0 && current.y == (N-1)) {
                cout << current.dist << endl;
                // printVisitedPlaces(visitedPlaces, C, M, N);
                // break;
                return 0;
                // return current.dist;
            }

            for (int i = 0; i < 4; ++i) {
                int newX = current.x + dx[i];
                int newY = current.y + dy[i];
                int absSwitchValue = abs(switchValue);
                // cout << newX << " " << newY << endl;
                if(isValid(newX, newY, M, N) == false) {
                    continue;
                }

                if(grid[newX][newY] <= 0 || grid[newX][newY] == absSwitchValue) {
                    if(visitedPlaces[absSwitchValue][newX * N + newY] == -1) {
                        // Empty place for visit
                        struct Node newNode;
                        newNode.x = newX;
                        newNode.y = newY;
                        newNode.dist = current.dist + 1;
                        
                        // Visited switch
                        if(grid[newX][newY] < 0) {
                            // Visited the switch of same color
                            // if(switchValue == grid[newX][newY]) {
                            //     int minValue = INT_MAX;
                            //     for (int i = 0; i <= C; ++i) {
                            //         // cout << visitedPlaces[i][newNode.x * N + newNode.y] << endl;
                            //         if(visitedPlaces[i][newNode.x * N + newNode.y] != -1) {
                            //             minValue = min(minValue, visitedPlaces[i][newNode.x * N + newNode.y]);
                            //         }
                            //     }
                            //     if(minValue != INT_MAX) {
                            //        newNode.dist = minValue; 
                            //     }
                            // }
                            q_switches.push(newNode);
                        }

                        q.push(newNode);
                        visitedPlaces[absSwitchValue][newNode.x * N + newNode.y] = newNode.dist;
                        // printVisitedPlaces(visitedPlaces, C, M, N);
                    }
                }
            }
        }
    }
    printVisitedPlaces(visitedPlaces, C, M, N);
    return 0;
}