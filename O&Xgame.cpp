#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// Function to calculate the sum of three integers
int sum(int a, int b, int c) {
    return a + b + c;
}

class TicTacToe {
private:
    vector<int> xState;
    vector<int> zState;
    int turn; // 1 for X and 0 for O
    stack<int> moves; // Stack to keep track of moves for undo functionality

public:
    TicTacToe() : xState(9, 0), zState(9, 0), turn(1) {}

    void printBoard() {
        char board[9];
        for (int i = 0; i < 9; ++i) {
            board[i] = (xState[i] ? 'X' : (zState[i] ? 'O' : '0' + i));
        }
        cout << board[0] << " | " << board[1] << " | " << board[2] << endl;
        cout << "--|---|---" << endl;
        cout << board[3] << " | " << board[4] << " | " << board[5] << endl;
        cout << "--|---|---" << endl;
        cout << board[6] << " | " << board[7] << " | " << board[8] << endl;
    }

    bool isValidMove(int move) {
        if (move < 0 || move > 8) {
            cout << "Invalid move. Please enter a number between 0 and 8." << endl;
            return false;
        }
        if (xState[move] || zState[move]) {
            cout << "That position is already taken. Please choose another." << endl;
            return false;
        }
        return true;
    }

    void makeMove(int move) {
        if (turn == 1) {
            xState[move] = 1;
        } else {
            zState[move] = 1;
        }
        moves.push(move); // Push the move onto the stack for undo functionality
    }

    void undoMove() {
        if (!moves.empty()) {
            int lastMove = moves.top();
            moves.pop();
            if (turn == 1) {
                xState[lastMove] = 0;
            } else {
                zState[lastMove] = 0;
            }
            turn = 1 - turn; // Switch turn back to the player who made the last move
        } else {
            cout << "No moves to undo." << endl;
        }
    }

    int checkWin() {
        vector<vector<int>> wins = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8},
                                    {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
                                    {0, 4, 8}, {2, 4, 6}};
        for (auto win : wins) {
            if (sum(xState[win[0]], xState[win[1]], xState[win[2]]) == 3) {
                cout << "X Won the match" << endl;
                return 1;
            }
            if (sum(zState[win[0]], zState[win[1]], zState[win[2]]) == 3) {
                cout << "O Won the match" << endl;
                return 0;
            }
        }
        return -1;
    }

    bool isBoardFull() {
        for (int i = 0; i < 9; ++i) {
            if (!xState[i] && !zState[i]) {
                return false;
            }
        }
        cout << "It's a draw!" << endl;
        return true;
    }

    void play() {
        cout << "Welcome to Tic Tac Toe" << endl;
        char firstPlayer;
        cout << "Who goes first? (X or O): ";
        cin >> firstPlayer;
        
        if (firstPlayer == 'X' || firstPlayer == 'x') {
            turn = 1; // X starts first
        } else {
            turn = 0; // O starts first
        }
        
        while (true) {
            printBoard();
            if (turn == 1) {
                cout << "X's Chance" << endl;
            } else {
                cout << "O's Chance" << endl;
            }
            int value;
            do {
                cout << "Please enter a value: ";
                cin >> value;
            } while (!isValidMove(value));
            
            makeMove(value);
            
            int cwin = checkWin();
            if (cwin != -1 || isBoardFull()) {
                cout << "Match over" << endl;
                break;
            }
            
            turn = 1 - turn;
        }
    }
};

int main() {
    TicTacToe game;
    game.play();
    return 0;
}
