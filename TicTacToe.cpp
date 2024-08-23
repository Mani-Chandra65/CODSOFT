#include <iostream>
using namespace std;

void CreateBoard(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

void DisplayBoard(char board[3][3]) {
    cout << "Current Board:\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << " " << board[i][j] << ' ';
            if (j < 2) cout << '|';
        }
        cout << endl;
        if (i < 2) {
            cout << "---|---|---\n";
        }
    }
    cout << endl;
}

bool placeMarker(char board[3][3], int slot, char marker) {
    int row = (slot - 1) / 3;
    int col = (slot - 1) % 3;

    if (board[row][col] == ' ') {
        board[row][col] = marker;
        return true;
    } else {
        return false;
    }
}

bool checkWinner(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') ||
            (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ')) {
            return true;
        }
    }
    if ((board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') ||
        (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')) {
        return true;
    }
    return false;
}

void input(char board[3][3], int player) {
    int slot;
    char marker = (player == 1) ? 'O' : 'X';
    
    do {
        cout << "Player " << player << " (" << marker << "), enter your position (1-9): ";
        cin >> slot;
        if (slot < 1 || slot > 9) {
            cout << "Invalid input! Please enter a number between 1 and 9." << endl;
        }
    } while (slot < 1 || slot > 9 || !placeMarker(board, slot, marker));

    DisplayBoard(board);
}

int main() {
    char board[3][3];
    CreateBoard(board);
    DisplayBoard(board);

    int player = 1;
    int turns = 0;
    bool gameWon = false;

    while (turns < 9 && !gameWon) {
        input(board, player);
        turns++;
        gameWon = checkWinner(board);
        if (gameWon) {
            cout << "Player " << player << " wins!" << endl;
        }
        player = (player == 1) ? 2 : 1;
    }

    if (!gameWon) {
        cout << "It's a tie!" << endl;
    }

    return 0;
}
