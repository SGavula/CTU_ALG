#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <cstdlib>
#include <climits>
#include <queue>

// push_back pushovanie do vecotru
// vector<vector<int>> matrix(rows, vector<int>(columns, 0));

using namespace std;

// Globally declared visited array
int vis[100];
 
// Graph structure to store number
// of vertices and edges and
// Adjacency matrix
struct Graph {
    int V;
    int E;
    vector<vector<int>> Adj;
};

// Function to input data of graph
struct Graph* adjMatrix() {
    struct Graph* G = new Graph;
    if (!G) {
        printf("Memory Error\n");
        return NULL;
    }
    G->V = 5;
    G->E = 5;
 
    G->Adj.resize(G->V, vector<int>(G->V, 0));

    G->Adj[0][1] = 1;
    G->Adj[0][2] = 1;
    G->Adj[0][3] = 1;
    
    G->Adj[1][0] = 1;
    G->Adj[1][3] = 1;
    
    G->Adj[2][0] = 1;
    G->Adj[2][3] = 1;

    G->Adj[3][0] = 1;
    G->Adj[3][1] = 1;
    G->Adj[3][2] = 1;
    G->Adj[3][4] = 1;
    
    G->Adj[4][3] = 1;
    return G;
}
 
 
// Function for DFS traversal
void DFStraversal(struct Graph* G, int v) {
    queue<int> q;

    q.push(v);
    
    while(!q.empty()) {
        int vertex = q.front();
        q.pop();
        // printf("%i\n", vertex);
        if(vis[vertex] == 0) {
            // Vertex is not visited
            // Visit vertex
            printf("%i ", vertex);
            vis[vertex] = 1;
            for (int i = 0; i < G->V; i++) {
                // printf("%i ", G->Adj[v][i]);
                if (vis[i] == 0 && G->Adj[vertex][i] == 1) {
                    q.push(i);
                    // printf("\nPush to stack: %i\n", i);
                }
            }
            // printf("\n");
        }
    }
}

/* Declarations of functions */

/* MAIN */
int main() {
    struct Graph* G;
    G = adjMatrix();
    printf("Number of vertexes: %i\n", G->V);
    printf("Number of edges: %i\n", G->E);
    for(int i = 0; i < G->V; i++) {
      for(int j = 0; j < G->V; j++) {
        printf("%i ", G->Adj[i][j]);
      }
      printf("\n");
    }
    DFStraversal(G, 0);
    printf("\n");

    return 0;
}

/* Definitions of functions */
