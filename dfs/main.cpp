#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <cstdlib>
#include <climits>

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
    G->V = 7;
    G->E = 7;
 
    G->Adj.resize(G->V, vector<int>(G->V, 0));

    G->Adj[0][1] = G->Adj[1][0] = 1;
    G->Adj[0][2] = G->Adj[2][0] = 1;
    G->Adj[1][3] = G->Adj[3][1] = 1;
    G->Adj[1][4] = G->Adj[4][1] = 1;
    G->Adj[1][5] = G->Adj[5][1] = 1;
    G->Adj[1][6] = G->Adj[6][1] = 1;
    G->Adj[6][2] = G->Adj[2][6] = 1;
 
    return G;
}
 
// DFS function to print DFS traversal of graph
void DFS(struct Graph* G, int u)
{

    vis[u] = 1;
    printf("%d ", u);
    for (int v = 0; v < G->V; v++) {
        if (vis[v] == 0 && G->Adj[u][v]) {
            DFS(G, v);
        }
    }
}
 
// Function for DFS traversal
void DFStraversal(struct Graph* G)
{
    for (int i = 0; i < 100; i++) {
        vis[i] = 0;
    }
    for (int i = 0; i < G->V; i++) {
        if (!vis[i]) {
            DFS(G, i);
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
    DFStraversal(G);
    printf("\n");

    return 0;
}

/* Definitions of functions */
