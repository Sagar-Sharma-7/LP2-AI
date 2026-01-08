#include <iostream>
#include <vector>
#include <chrono>
#include <limits>

using namespace std;
using namespace chrono;

long long statesExplored = 0;

// Print board
void printBoard(const vector<char>& board) {
    cout << endl;
    for (int i = 0; i < 9; i++) {
        cout << board[i] << " ";
        if ((i + 1) % 3 == 0)
            cout << endl;
    }
    cout << endl;
}

// Check winner
char checkWinner(const vector<char>& board) {
    int win[8][3] = {
        {0,1,2},{3,4,5},{6,7,8},
        {0,3,6},{1,4,7},{2,5,8},
        {0,4,8},{2,4,6}
    };

    for (auto& w : win) {
        if (board[w[0]] != '_' &&
            board[w[0]] == board[w[1]] &&
            board[w[1]] == board[w[2]])
            return board[w[0]];
    }
    return '_';
}

// Check if moves remain
bool isMovesLeft(const vector<char>& board) {
    for (char c : board)
        if (c == '_')
            return true;
    return false;
}

// DFS + Minimax
int minimax(vector<char>& board, bool isMax) {
    statesExplored++;

    char winner = checkWinner(board);
    if (winner == 'X') return 10;
    if (winner == 'O') return -10;
    if (!isMovesLeft(board)) return 0;

    if (isMax) {
        int best = numeric_limits<int>::min();
        for (int i = 0; i < 9; i++) {
            if (board[i] == '_') {
                board[i] = 'X';
                best = max(best, minimax(board, false));
                board[i] = '_';  // backtrack
            }
        }
        return best;
    } else {
        int best = numeric_limits<int>::max();
        for (int i = 0; i < 9; i++) {
            if (board[i] == '_') {
                board[i] = 'O';
                best = min(best, minimax(board, true));
                board[i] = '_';  // backtrack
            }
        }
        return best;
    }
}

// Find best move for AI
int findBestMove(vector<char>& board) {
    int bestVal = numeric_limits<int>::min();
    int bestMove = -1;

    for (int i = 0; i < 9; i++) {
        if (board[i] == '_') {
            board[i] = 'X';

            int moveVal = minimax(board, false);

            board[i] = '_';

            if (moveVal > bestVal) {
                bestMove = i;
                bestVal = moveVal;
            }
        }
    }
    return bestMove;
}

int main() {
    vector<char> board(9, '_');
    int move;
    char winner;

    cout << "Tic-Tac-Toe (Human vs AI)\n";
    cout << "You are O, AI is X\n";
    cout << "Positions: 0 1 2 / 3 4 5 / 6 7 8\n";

    printBoard(board);

    while (true) {
        // Human move
        cout << "Enter your move (0-8): ";
        cin >> move;

        if (move < 0 || move > 8 || board[move] != '_') {
            cout << "Invalid move. Try again.\n";
            continue;
        }

        board[move] = 'O';
        printBoard(board);

        winner = checkWinner(board);
        if (winner == 'O') {
            cout << "🎉 You win!\n";
            break;
        }
        if (!isMovesLeft(board)) {
            cout << "It's a draw!\n";
            break;
        }

        // AI move
        statesExplored = 0;
        auto start = high_resolution_clock::now();

        int bestMove = findBestMove(board);
        board[bestMove] = 'X';

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);

        cout << "AI played at position: " << bestMove << endl;
        cout << "AI states explored: " << statesExplored << endl;
        cout << "AI move time: " << duration.count() << " microseconds\n";

        printBoard(board);

        winner = checkWinner(board);
        if (winner == 'X') {
            cout << "🤖 AI wins!\n";
            break;
        }
        if (!isMovesLeft(board)) {
            cout << "It's a draw!\n";
            break;
        }
    }

    return 0;
}
