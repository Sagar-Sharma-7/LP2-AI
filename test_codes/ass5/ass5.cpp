#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
using namespace std;

/*
====================================================
Program Implements:
1. Single Source Shortest Path Problem (Dijkstra)
2. Job Scheduling Problem (Greedy)
====================================================
*/

// -------------------------------------------------
// Part 1: Single Source Shortest Path using Dijkstra
// -------------------------------------------------
struct Edge {
    int to, weight;
};

void dijkstra(int vertices, vector<vector<Edge>>& graph, int source) {
    vector<int> dist(vertices, INT_MAX);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u]) continue;

        for (auto edge : graph[u]) {
            int v = edge.to;
            int w = edge.weight;

            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    cout << "\nShortest Distance from Source " << source << ":\n";
    for (int i = 0; i < vertices; i++) {
        cout << "To " << i << " = " << dist[i] << endl;
    }
}

// -------------------------------------------------
// Part 2: Job Scheduling Problem
// -------------------------------------------------
struct Job {
    char id;
    int deadline;
    int profit;
};

bool compareJob(Job a, Job b) {
    return a.profit > b.profit;
}

void jobScheduling(vector<Job>& jobs) {
    sort(jobs.begin(), jobs.end(), compareJob);

    int maxDeadline = 0;
    for (auto job : jobs)
        maxDeadline = max(maxDeadline, job.deadline);

    vector<char> slot(maxDeadline + 1, '-');
    int totalProfit = 0;

    for (auto job : jobs) {
        for (int j = job.deadline; j >= 1; j--) {
            if (slot[j] == '-') {
                slot[j] = job.id;
                totalProfit += job.profit;
                break;
            }
        }
    }

    cout << "\nSelected Jobs:\n";
    for (int i = 1; i <= maxDeadline; i++) {
        if (slot[i] != '-')
            cout << slot[i] << " ";
    }

    cout << "\nTotal Profit = " << totalProfit << endl;
}

// -------------------------------------------------
// Main Function
// -------------------------------------------------
int main() {
    int choice;

    cout << "Choose Operation:\n";
    cout << "1. Single Source Shortest Path\n";
    cout << "2. Job Scheduling Problem\n";
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 1) {
        int v, e;
        cout << "Enter number of vertices: ";
        cin >> v;

        cout << "Enter number of edges: ";
        cin >> e;

        vector<vector<Edge>> graph(v);

        cout << "Enter edges (u v weight):\n";
        for (int i = 0; i < e; i++) {
            int u, vv, w;
            cin >> u >> vv >> w;
            graph[u].push_back({vv, w});
            graph[vv].push_back({u, w}); // undirected graph
        }

        int source;
        cout << "Enter source vertex: ";
        cin >> source;

        dijkstra(v, graph, source);
    }

    else if (choice == 2) {
        int n;
        cout << "Enter number of jobs: ";
        cin >> n;

        vector<Job> jobs(n);

        cout << "Enter job details (id deadline profit):\n";
        for (int i = 0; i < n; i++) {
            cin >> jobs[i].id >> jobs[i].deadline >> jobs[i].profit;
        }

        jobScheduling(jobs);
    }

    else {
        cout << "Invalid Choice";
    }

    return 0;
}

/*
====================================================
Dummy Input Test Case 1: Single Source Shortest Path
====================================================

Enter choice: 1
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
Dummy Input Test Case 2: Job Scheduling Problem
====================================================

Enter choice: 2
Enter number of jobs: 5

Enter job details (id deadline profit):
A 2 100
B 1 19
C 2 27
D 1 25
E 3 15

Expected Output:
Selected Jobs:
C A E
Total Profit = 142

====================================================
*/