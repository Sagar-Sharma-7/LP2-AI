#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
using namespace std;

/*
====================================================
Program Implements (One from the following):
1. Kruskal's Minimum Spanning Tree Algorithm
2. Dijkstra's Algorithm (Shortest Path)

Note:
Dijkstra is used for shortest path, not MST.
Many assignments write it as "Dijkstra's MST" by mistake.
====================================================
*/

// -------------------------------------------------
// Part 1: Kruskal's Minimum Spanning Tree
// -------------------------------------------------
struct Edge {
    int u, v, w;
};

bool compareEdge(Edge a, Edge b) {
    return a.w < b.w;
}

class DSU {
    vector<int> parent, rankArr;

public:
    DSU(int n) {
        parent.resize(n);
        rankArr.resize(n, 0);

        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);

        return parent[x];
    }

    void unite(int x, int y) {
        int px = find(x);
        int py = find(y);

        if (px == py) return;

        if (rankArr[px] < rankArr[py])
            parent[px] = py;
        else if (rankArr[px] > rankArr[py])
            parent[py] = px;
        else {
            parent[py] = px;
            rankArr[px]++;
        }
    }
};

void kruskal(int v, vector<Edge>& edges) {
    sort(edges.begin(), edges.end(), compareEdge);

    DSU dsu(v);
    int total = 0;

    cout << "\nEdges in MST:\n";

    for (auto e : edges) {
        if (dsu.find(e.u) != dsu.find(e.v)) {
            dsu.unite(e.u, e.v);
            cout << e.u << " - " << e.v << " : " << e.w << endl;
            total += e.w;
        }
    }

    cout << "Total Cost = " << total << endl;
}

// -------------------------------------------------
// Part 2: Dijkstra Shortest Path
// -------------------------------------------------
struct Node {
    int to, wt;
};

void dijkstra(int v, vector<vector<Node>>& graph, int source) {
    vector<int> dist(v, INT_MAX);

    priority_queue<
        pair<int,int>,
        vector<pair<int,int>>,
        greater<pair<int,int>>
    > pq;

    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u]) continue;

        for (auto edge : graph[u]) {
            int next = edge.to;
            int w = edge.wt;

            if (dist[u] + w < dist[next]) {
                dist[next] = dist[u] + w;
                pq.push({dist[next], next});
            }
        }
    }

    cout << "\nShortest Distance from Source " << source << ":\n";
    for (int i = 0; i < v; i++) {
        cout << "To " << i << " = " << dist[i] << endl;
    }
}

// -------------------------------------------------
// Main Function
// -------------------------------------------------
int main() {
    int choice;

    cout << "Choose Algorithm:\n";
    cout << "1. Kruskal MST\n";
    cout << "2. Dijkstra Shortest Path\n";
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 1) {
        int v, e;
        cout << "Enter number of vertices: ";
        cin >> v;

        cout << "Enter number of edges: ";
        cin >> e;

        vector<Edge> edges(e);

        cout << "Enter edges (u v weight):\n";
        for (int i = 0; i < e; i++) {
            cin >> edges[i].u >> edges[i].v >> edges[i].w;
        }

        kruskal(v, edges);
    }
    else if (choice == 2) {
        int v, e;
        cout << "Enter number of vertices: ";
        cin >> v;

        cout << "Enter number of edges: ";
        cin >> e;

        vector<vector<Node>> graph(v);

        cout << "Enter edges (u v weight):\n";
        for (int i = 0; i < e; i++) {
            int u, vv, w;
            cin >> u >> vv >> w;

            graph[u].push_back({vv, w});
            graph[vv].push_back({u, w});
        }

        int source;
        cout << "Enter source vertex: ";
        cin >> source;

        dijkstra(v, graph, source);
    }
    else {
        cout << "Invalid Choice";
    }

    return 0;
}

/*
====================================================
Dummy Input Test Case 1: Kruskal MST
====================================================

Enter choice: 1
Enter number of vertices: 4
Enter number of edges: 5

Enter edges (u v weight):
0 1 10
0 2 6
0 3 5
1 3 15
2 3 4

Expected Output:
Edges in MST:
2 - 3 : 4
0 - 3 : 5
0 - 1 : 10
Total Cost = 19


====================================================
Dummy Input Test Case 2: Dijkstra
====================================================

Enter choice: 2
Enter number of vertices: 5
Enter number of edges: 6

Enter edges (u v weight):
0 1 2
0 2 4
1 2 1
1 3 7
2 4 3
3 4 1

Enter source vertex: 0

Expected Output:
Shortest Distance from Source 0:
To 0 = 0
To 1 = 2
To 2 = 3
To 3 = 7
To 4 = 6

====================================================
*/