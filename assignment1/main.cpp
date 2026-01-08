#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;


class Graph {
public:
    unordered_map<int, vector<int>> adj;

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
};

void DFS(int node, unordered_map<int, vector<int>>& adj, unordered_set<int>& visited) {
    visited.insert(node);
    cout << node << " ";

    for (int neighbor : adj[node]) {
        if (visited.find(neighbor) == visited.end()) {
            DFS(neighbor, adj, visited);
        }
    }
}


void DFS_Full(Graph& g) {
    unordered_set<int> visited;

    for (auto& pair : g.adj) {
        int vertex = pair.first;
        if (visited.find(vertex) == visited.end()) {
            DFS(vertex, g.adj, visited);
        }
    }
}


void BFS(int start, unordered_map<int, vector<int>>& adj) {
    unordered_set<int> visited;
    queue<int> q;

    visited.insert(start);
    q.push(start);

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        cout << node << " ";

        for (int neighbor : adj[node]) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                q.push(neighbor);
            }
        }
    }
}

void BFS_Full(Graph& g) {
    unordered_set<int> visited;

    for (auto& pair : g.adj) {
        int start = pair.first;

        if (visited.find(start) == visited.end()) {
            queue<int> q;
            q.push(start);
            visited.insert(start);

            while (!q.empty()) {
                int node = q.front();
                q.pop();
                cout << node << " ";

                for (int neighbor : g.adj[node]) {
                    if (visited.find(neighbor) == visited.end()) {
                        visited.insert(neighbor);
                        q.push(neighbor);
                    }
                }
            }
        }
    }
}

int main() {
    Graph g;

    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(2, 5);
    g.addEdge(3, 6);
    g.addEdge(5, 6);

    cout << "DFS Traversal (Recursive): ";
    unordered_set<int> visited;
    DFS(1, g.adj, visited);

    cout << "\nBFS Traversal: ";
    BFS(1, g.adj);

    return 0;
}
