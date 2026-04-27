#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class GraphTree {
private:
    int vertices;
    vector<vector<int>> adj;
    vector<bool> visited;

public:
    GraphTree(int v) {
        vertices = v;
        adj.resize(v);
        visited.resize(v, false);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // Undirected graph / tree
    }

    void resetVisited() {
        for (int i = 0; i < vertices; i++) {
            visited[i] = false;
        }
    }

    // Recursive DFS for Graph / Tree
    void DFS(int node) {
        visited[node] = true;
        cout << node << " ";

        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                DFS(neighbor);
            }
        }
    }

    // BFS for Graph / Tree
    void BFS(int start) {
        queue<int> q;
        visited[start] = true;
        q.push(start);

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            cout << node << " ";

            for (int neighbor : adj[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
    }
};

int main() {
    int v, e, choice;

    cout << "Choose Structure:\n";
    cout << "1. Graph\n";
    cout << "2. Tree\n";
    cout << "Enter choice: ";
    cin >> choice;

    cout << "Enter number of vertices: ";
    cin >> v;

    GraphTree gt(v);

    if (choice == 1) {
        cout << "Enter number of edges: ";
        cin >> e;
        cout << "Enter edges (u v):\n";

        for (int i = 0; i < e; i++) {
            int u, w;
            cin >> u >> w;
            gt.addEdge(u, w);
        }
    }
    else if (choice == 2) {
        cout << "For Tree, enter " << v - 1 << " edges:\n";

        for (int i = 0; i < v - 1; i++) {
            int u, w;
            cin >> u >> w;
            gt.addEdge(u, w);
        }
    }
    else {
        cout << "Invalid Choice";
        return 0;
    }

    int start;
    cout << "Enter starting vertex: ";
    cin >> start;

    cout << "\nDFS Traversal: ";
    gt.resetVisited();
    gt.DFS(start);

    cout << "\nBFS Traversal: ";
    gt.resetVisited();
    gt.BFS(start);

    return 0;
}

/*
=========================
Dummy Input Test Case 1
(Graph)
=========================

Enter choice: 1
Enter number of vertices: 6
Enter number of edges: 7
Enter edges:
0 1
0 2
1 3
1 4
2 5
3 4
4 5
Enter starting vertex: 0

Output:
DFS Traversal: 0 1 3 4 5 2
BFS Traversal: 0 1 2 3 4 5


=========================
Dummy Input Test Case 2
(Tree)
=========================

Enter choice: 2
Enter number of vertices: 6
Enter edges:
0 1
0 2
1 3
1 4
2 5
Enter starting vertex: 0

Output:
DFS Traversal: 0 1 3 4 2 5
BFS Traversal: 0 1 2 3 4 5
*/