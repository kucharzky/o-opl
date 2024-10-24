#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <set>

using namespace std;

const int SIZE = 10;
char board[SIZE][SIZE];

// Positions for player, treasure, and traps
int playerX, playerY;
pair<int, int> treasure;
vector<pair<int, int>> traps;

// Helper function to print the board
void printBoard() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cout << board[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

// Check if the position is out of bounds
bool isOutOfBounds(int x, int y) {
    return x < 0 || x >= SIZE || y < 0 || y >= SIZE;
}

// Generate a random empty position on the board
pair<int, int> getRandomEmptyPosition(set<pair<int, int>>& usedPositions) {
    int x, y;
    do {
        x = rand() % SIZE;
        y = rand() % SIZE;
    } while (usedPositions.count({x, y}) > 0); // Ensure it's not already taken
    usedPositions.insert({x, y}); // Mark this position as used
    return {x, y};
}

// Initialize the board and place the player, treasure, and traps
void initializeBoard(int numTraps) {
    // Clear the board
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            board[i][j] = '.';

    // Keep track of used positions
    set<pair<int, int>> usedPositions;

    // Place the player ('P')
    pair<int, int> playerPos = getRandomEmptyPosition(usedPositions);
    playerX = playerPos.first;
    playerY = playerPos.second;
    board[playerX][playerY] = 'P';

    // Place the treasure ('T')
    treasure = getRandomEmptyPosition(usedPositions);
    board[treasure.first][treasure.second] = 'T';

    // Place traps ('X')
    traps.clear();
    for (int i = 0; i < numTraps; i++) {
        pair<int, int> trapPos = getRandomEmptyPosition(usedPositions);
        traps.push_back(trapPos);
        board[trapPos.first][trapPos.second] = 'X';
    }
}

// Move the player based on input
void movePlayer(char direction) {
    int newX = playerX, newY = playerY;

    switch (direction) {
        case 'U': newX--; break; // Move up
        case 'D': newX++; break; // Move down
        case 'L': newY--; break; // Move left
        case 'R': newY++; break; // Move right
        default: cout << "Invalid move!" << endl; return;
    }

    // Check bounds
    if (isOutOfBounds(newX, newY)) {
        cout << "You can't move outside the board!" << endl;
        return;
    }

    // Check if stepping on a trap
    if (board[newX][newY] == 'X') {
        cout << "You stepped on a trap! You lose!" << endl;
        exit(0);
    }

    // Check if stepping on the treasure
    if (board[newX][newY] == 'T') {
        cout << "You found the treasure! You win!" << endl;
        exit(0);
    }

    // Move the player
    board[playerX][playerY] = '.';  // Clear old position
    playerX = newX;
    playerY = newY;
    board[playerX][playerY] = 'P';  // Update to new position
}

// Move traps randomly after the player's move
void moveTraps() {
    srand(time(0));

    for (auto &trap : traps) {
        int x = trap.first;
        int y = trap.second;

        // Clear the trap's old position
        board[x][y] = '.';

        // Randomly move trap by one position
        int direction = rand() % 4;
        switch (direction) {
            case 0: if (!isOutOfBounds(x - 1, y)) trap.first--; break; // Move up
            case 1: if (!isOutOfBounds(x + 1, y)) trap.first++; break; // Move down
            case 2: if (!isOutOfBounds(x, y - 1)) trap.second--; break; // Move left
            case 3: if (!isOutOfBounds(x, y + 1)) trap.second++; break; // Move right
        }

        // Check if trap moves onto the player
        if (trap.first == playerX && trap.second == playerY) {
            cout << "A trap moved onto you! You lose!" << endl;
            exit(0);
        }

        // Update new trap position
        board[trap.first][trap.second] = 'X';
    }
}

int main() {
    srand(time(0));  // Initialize random seed

    int numTraps = 5; // Number of traps to place
    initializeBoard(numTraps);

    char move;

    while (true) {
        printBoard();
        cout << "Enter move (U/D/L/R): ";
        cin >> move;

        movePlayer(move);
        moveTraps();
    }

    return 0;
}
