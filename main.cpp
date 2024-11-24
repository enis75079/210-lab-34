/*

lab34: network graph
COMSC-210
Naveen Islam
IDE: vscode

*/
#include <iostream>
#include <vector>
using namespace std;

// changed SIZE to include the new nodes
const int SIZE = 9;


struct Edge {
    int src, dest, weight;
};

typedef pair<int, int> Pair;  // Creates alias 'Pair' for the pair<int,int> data type

class Graph {
public:
    // a vector of vectors of Pairs to represent an adjacency list
    vector<vector<Pair>> adjList;

    // Graph Constructor
    Graph(vector<Edge> const &edges) {
        // resize the vector to hold SIZE elements of type vector<Edge>
        adjList.resize(SIZE);

        // add edges to the directed graph
        for (auto &edge: edges) {
            int src = edge.src;
            int dest = edge.dest;
            int weight = edge.weight;

            // insert at the end
            adjList[src].push_back(make_pair(dest, weight));
            // for an undirected graph, add an edge from dest to src also
            adjList[dest].push_back(make_pair(src, weight));
        }

        // sorts the ajd list for consistent DFS
        for (auto &adj : adjList) {
            for (int i = 0; i < adj.size(); i++) {
                for (size_t j = i + 1; j < adj.size(); j++) {
                    if (adj[j].first < adj[i].first) {
                        swap(adj[i], adj[j]);
                    }
                }    
            }
        }
    }

    // Print the graph's adjacency list
    void printGraph() {
        cout << "Freight Delivery Network Topology:" << endl;
        cout << "++++++++++++++++++++++++++++++++++" << endl;
        cout << endl;
        for (int i = 0; i < adjList.size(); i++) {
            cout << "Warehouse " << i << " connects to:" << endl;
            for (Pair v : adjList[i])
                cout << "  - Warehouse " << v.first << " (Distance: " << v.second << " miles)" << endl;
            cout << endl;
        }
    }

    // DFS function. (recursive)
    void DFS(int startingInt) {
        // tracks the nodes that have been visited
        vector<bool> visitedNodes(SIZE, false);
        cout << "Tracing Freight Delivery Routes (DFS) from Warehouse " << startingInt << ": \n";
        // calls the recursion
        DFSRecursive(startingInt, visitedNodes, 0);
        cout << endl;
    }

    void DFSRecursive(int currentIndex, vector<bool>& passedNodes, int totalDistance) {
        // sets the current index as visited (true) and prints the node
        passedNodes[currentIndex] = true;
        cout << "Visitng Warehouse " << currentIndex << " (Total Distance Traveled: " << totalDistance << " miles)" << endl;

        // recursion for the adjacent nodes that havent been visited yet
        for (auto &adj : adjList[currentIndex]) {
            if (!passedNodes[adj.first]) {
                DFSRecursive(adj.first, passedNodes, totalDistance + adj.second);
            }
        }
    }

    // BFS function
    void BFS(int startingInt) {
        // tracks the nodes that have been visited
        vector<bool> visitedNodes(SIZE, false);

        // array for what is next during current node
        int next[SIZE];
        int front = 0;
        int back = 0;
        int currentLayer = 0;
        int warehouse = 0;

        cout << "\nInspecting Freight Distrubution Layers (BFS) from Warehouse " << startingInt << ":\n";
        visitedNodes[startingInt] = true;
        next[back++] = startingInt;

        while (front < back) {
            int numNodes = back - front;
            cout << "Layer " << currentLayer++ << endl;
            
            for (int i = 0; i < numNodes; i++) {
                int warehouse = next[front++];
                cout << "  - Warehouse " << warehouse << endl;
            
                // adds all unvisited neighboring ndoes to the queue
                for (auto &adj : adjList[warehouse]) {
                    if (!visitedNodes[adj.first]) {
                        visitedNodes[adj.first] = true;
                        next[back++] = adj.first;
                    }
                }
            }
            cout << endl;
        }
    }

    void shortestPath(int startingInt) {
        int largeVal = 9999;
        int distance[SIZE];
        bool visitedNodes[SIZE];

        for (int i = 0; i <SIZE; i++) {
            distance[i] = largeVal;
            visitedNodes[i] = false;
        }
        distance[startingInt] = 0;

        for (int count = 0; count < SIZE - 1; count++) {
            int minDistance = largeVal;
            int u = -1;

            for (int i = 0; i < SIZE; i++) {
                if (!visitedNodes[i] && distance[i] < minDistance) {
                    minDistance = distance[i];
                    u = i;
                }
            }

            visitedNodes[u] = true;

            for (auto &adj : adjList[u]) {
                int v = adj.first;
                int weight = adj.second;

                if (!visitedNodes[v] && distance[u] + weight < distance[v]) {
                    distance[v] = distance[u] + weight;
                }    
            }
        }
        cout << "Shortest path from node " << startingInt << ":\n";
        for (int i = 0; i <SIZE; i++) {
            cout << startingInt << " -> " << i << " : " << distance[i] << endl;
        }
    }

    void MST() {
        int largeVal = 9999;
        int u = 0;
        int v = 0;
        vector<int> key(SIZE, largeVal);
        vector<int> inMST(SIZE, false);
        vector<bool> parent(SIZE, -1);

        key[0] = 0;

        for (int count = 0; count < SIZE - 1; count++) {
            int u = -1;
        
            for (int i = 0; i < SIZE; i++) {
                if (!inMST[i] && (u == -1 || key[i] < key[u])) {
                    u = i;
                }
            }
            inMST[u] = true;

            for (auto &adj : adjList[u]) {
                int v = adj.first;
                int weight = adj.second;

                if (!inMST[v] && weight < key[v]) {
                    key[v] = weight;
                    parent[v] = u;
                }    
            }
        }

        cout << "Minimum Spanning Tree edges:" << endl;
        for (int i = 1; i < SIZE; i++) {
            if (parent[i] != -1) {
                cout << "Edge from " << parent[i] << " to " << i << " with capacity: " << key[i] << " units" << endl;
            }
        }
    }
};

int main() {
    // Creates a vector of graph edges/weights
    vector<Edge> edges = {
        // (x, y, w) —> edge from x to y having weight w
        {0, 1, 8}, {0, 2, 21}, {0, 8, 2}, {1, 3, 4}, {2, 3, 6}, {2, 4, 4}, {2, 6, 2}, {3, 5, 9},
        {4, 5, 10}, {5, 6, 6}, {6, 7, 15}, {7, 8, 11}, {6, 8, 7}
    };

    // Creates graph
    Graph graph(edges);

    // Prints adjacency list representation of graph
    graph.printGraph();

    // call shortestPath function
    graph.MST();
    // Step 4 complete.
    return 0;
}
