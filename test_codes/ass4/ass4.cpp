#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
====================================================
Program implements:
1. Selection Sort
2. Minimum Spanning Tree (Kruskal's Algorithm)
====================================================
*/

// -------------------- Selection Sort --------------------
void selectionSort(vector<int>& arr) {
    int n = arr.size();

    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;

        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        swap(arr[i], arr[minIndex]);
    }
}

// -------------------- MST using Kruskal --------------------
struct Edge {
    int u, v, weight;
};

bool compareEdge(Edge a, Edge b) {
    return a.weight < b.weight;
}

class DSU {
private:
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

        if (rankArr[px] < rankArr[py]) {
            parent[px] = py;
        }
        else if (rankArr[px] > rankArr[py]) {
            parent[py] = px;
        }
        else {
            parent[py] = px;
            rankArr[px]++;
        }
    }
};

void kruskalMST(int vertices, vector<Edge>& edges) {
    sort(edges.begin(), edges.end(), compareEdge);

    DSU dsu(vertices);

    int totalCost = 0;

    cout << "\nEdges in Minimum Spanning Tree:\n";

    for (Edge e : edges) {
        if (dsu.find(e.u) != dsu.find(e.v)) {
            dsu.unite(e.u, e.v);
            cout << e.u << " - " << e.v << " : " << e.weight << endl;
            totalCost += e.weight;
        }
    }

    cout << "Total Cost of MST = " << totalCost << endl;
}

// -------------------- Main --------------------
int main() {
    int choice;

    cout << "Choose Operation:\n";
    cout << "1. Selection Sort\n";
    cout << "2. Minimum Spanning Tree\n";
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 1) {
        int n;
        cout << "Enter number of elements: ";
        cin >> n;

        vector<int> arr(n);

        cout << "Enter elements:\n";
        for (int i = 0; i < n; i++)
            cin >> arr[i];

        selectionSort(arr);

        cout << "Sorted Array:\n";
        for (int x : arr)
            cout << x << " ";

        cout << endl;
    }

    else if (choice == 2) {
        int v, e;
        cout << "Enter number of vertices: ";
        cin >> v;

        cout << "Enter number of edges: ";
        cin >> e;

        vector<Edge> edges(e);

        cout << "Enter edges (u v weight):\n";
        for (int i = 0; i < e; i++) {
            cin >> edges[i].u >> edges[i].v >> edges[i].weight;
        }

        kruskalMST(v, edges);
    }

    else {
        cout << "Invalid Choice";
    }

    return 0;
}

/*
====================================================
Dummy Input Test Case 1: Selection Sort
====================================================

Enter choice: 1
Enter number of elements: 5
Enter elements:
64 25 12 22 11

Expected Output:
Sorted Array:
11 12 22 25 64


====================================================
Dummy Input Test Case 2: Minimum Spanning Tree
====================================================

Enter choice: 2
Enter number of vertices: 4
Enter number of edges: 5

Enter edges (u v weight):
0 1 10
0 2 6
0 3 5
1 3 15
2 3 4

Expected Output:
Edges in Minimum Spanning Tree:
2 - 3 : 4
0 - 3 : 5
0 - 1 : 10
Total Cost of MST = 19

====================================================
*/