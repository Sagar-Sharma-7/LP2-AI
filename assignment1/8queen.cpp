#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace chrono;

const int N = 8;

vector<vector<int>> solutions;
long long recursiveCalls = 0;

/*
 Check if placing a queen at (row, col) is safe
*/
bool isSafe(vector<int>& board, int row, int col) {
    for (int i = 0; i < row; i++) {
        // Same column
        if (board[i] == col)
            return false;

        // Diagonals
        if (abs(board[i] - col) == row - i)
            return false;
    }
    return true;
}

/*
 DFS + Backtracking
*/
void solveNQueens(vector<int>& board, int row) {
    recursiveCalls++;

    // Base case: all queens placed
    if (row == N) {
        solutions.push_back(board);
        return;
    }

    // Try placing queen in each column
    for (int col = 0; col < N; col++) {
        if (isSafe(board, row, col)) {
            board[row] = col;          // Place queen
            solveNQueens(board, row + 1);
            board[row] = -1;           // Backtrack
        }
    }
}

/*
 Print a solution
*/
void printSolution(const vector<int>& board) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i] == j)
                cout << "Q ";
            else
                cout << ". ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    vector<int> board(N, -1);

    // Start timing
    auto start = high_resolution_clock::now();

    solveNQueens(board, 0);

    // Stop timing
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    // Output results
    cout << "Total Solutions: " << solutions.size() << endl;
    cout << "Total Recursive Calls (States Explored): " << recursiveCalls << endl;
    cout << "Time Taken: " << duration.count() << " ms" << endl;

    // Print solutions (optional)
    cout << "\nPrinting solutions:\n";
    for (const auto& sol : solutions) {
        printSolution(sol);
    }

    return 0;
}
