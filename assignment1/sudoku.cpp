#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;

const int N = 9;
long long statesExplored = 0;

// Print Sudoku grid
void printGrid(int grid[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

// Check if num can be placed at grid[row][col]
bool isSafe(int grid[N][N], int row, int col, int num) {
    // Check row and column
    for (int x = 0; x < N; x++) {
        if (grid[row][x] == num || grid[x][col] == num)
            return false;
    }

    // Check 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[startRow + i][startCol + j] == num)
                return false;

    return true;
}

// DFS + Backtracking Sudoku Solver
bool solveSudoku(int grid[N][N]) {
    statesExplored++;

    int row = -1, col = -1;
    bool emptyFound = false;

    // Find an empty cell
    for (int i = 0; i < N && !emptyFound; i++) {
        for (int j = 0; j < N; j++) {
            if (grid[i][j] == 0) {
                row = i;
                col = j;
                emptyFound = true;
                break;
            }
        }
    }

    // No empty cell -> solved
    if (!emptyFound)
        return true;

    // Try digits 1 to 9
    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;

            if (solveSudoku(grid))
                return true;

            grid[row][col] = 0; // Backtrack
        }
    }
    return false;
}

int main() {
    int grid[N][N] = {
        {5,3,0,0,7,0,0,0,0},
        {6,0,0,1,9,5,0,0,0},
        {0,9,8,0,0,0,0,6,0},
        {8,0,0,0,6,0,0,0,3},
        {4,0,0,8,0,3,0,0,1},
        {7,0,0,0,2,0,0,0,6},
        {0,6,0,0,0,0,2,8,0},
        {0,0,0,4,1,9,0,0,5},
        {0,0,0,0,8,0,0,7,9}
    };

    cout << "Original Sudoku:\n";
    printGrid(grid);

    auto start = high_resolution_clock::now();

    if (solveSudoku(grid)) {
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);

        cout << "\nSolved Sudoku:\n";
        printGrid(grid);

        cout << "\nStates Explored (DFS calls): " << statesExplored << endl;
        cout << "Time Taken: " << duration.count() << " microseconds" << endl;
    } else {
        cout << "No solution exists." << endl;
    }

    return 0;
}
