/*

lab34: network graph
COMSC-210
Naveen Islam
IDE: vscode

*/
#include <iostream>
#include <vector>
using namespace std;

const int SIZE = 7;

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
    }

    // Print the graph's adjacency list
    void printGraph() {
        cout << "Graph's adjacency list:" << endl;
        for (int i = 0; i < adjList.size(); i++) {
            cout << i << " --> ";
            for (Pair v : adjList[i])
                cout << "(" << v.first << ", " << v.second << ") ";
            cout << endl;
        }
    }

    // DFS function. (recursive)
    void DFS(int startingInt) {
        // tracks the nodes that have been visited
        vector<bool> visitedNodes(SIZE, false);
        cout << "DFS starting from vertex " << startingInt << ": \n";
        // calls the recursion
        DFSRecursive(startingInt, visitedNodes);
        cout << endl;
    }

    void DFSRecursive(int currentIndex, vector<bool>& passedNodes) {
        // sets the current index as visited (true) and prints the node
        passedNodes[currentIndex] = true;
        cout << currentIndex << " ";

        // recursion for the adjacent nodes that havent been visited yet
        for (auto &adj : adjList[currentIndex]) {
            if (!passedNodes[adj.first]) {
                DFSRecursive(adj.first, passedNodes);
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

        cout << "BFS starting from vertex " << startingInt << ": \n";
        visitedNodes[startingInt] = true;
        next[back] = startingInt;
        back++;

        while (front < back) {
            int currentIndex = next[front];
            front++;
            cout << currentIndex << " ";

            // adds all unvisited neighboring ndoes to the queue
            for (auto &adj : adjList[currentIndex]) {
                if (!visitedNodes[adj.first]) {
                    visitedNodes[adj.first] = true;
                    next[back] = adj.first;
                    back++;
                }
            }
        }
        cout << endl;
    }
};

int main() {
    // Creates a vector of graph edges/weights
    vector<Edge> edges = {
        // (x, y, w) —> edge from x to y having weight w
        {0,1,12},{0,2,8},{0,3,21},{2,3,6},{2,6,2},{5,6,6},{4,5,9},{2,4,4},{2,5,5}
    };

    // Creates graph
    Graph graph(edges);

    // Prints adjacency list representation of graph
    graph.printGraph();

    // calls DFS and BFS
    graph.DFS(0);
    graph.BFS(0);
    return 0;
}
