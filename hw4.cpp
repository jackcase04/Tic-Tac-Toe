// Programmer: Jack Case
// Date: 02/29/2024
// File: hw4.cpp
// Assignment: HW2
// Purpose: A program that allows players to play a game of tic-tac-toe.

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void printWelcomeMessage();

// No parameters, function prints a Welcome message to the user.

void printWelcomeMessage() {
    cout << "Welcome to Dynamic Tic-Tac-Toe Missouri S&T Edition!" << endl;
}

void displayMenu();

// No parameters, prints a display message to the user that shows the options for size of the board.

void displayMenu() {
    cout << "Choose the size of the Tic-Tac-Toe board or Quit:" << endl << "1. 3x3 Board" << endl << "2. 4x4 Board" << endl << "3. 5x5 Board" << endl << "4. 6x6 Board" << endl << "5. 7x7 Board" << endl << "6. 8x8 Board" << endl << "7. 9x9 Board" << endl << "8. Quit the Program" << endl;
}

string initializeBoard(const int size);

// This function initalizes the string that will represent the board after the user chooses what size the board should be.
// One parameter "size" which is the size of the board.
// Returns a string "board" which will represent the board.

string initializeBoard(const int size) {
    string board;
    // loop that iterates through 0 to the size of the board, adding i to the string each time.
    for(int i = 1; i<= (size*size); ++i) {
        if (i < 10) { 
            board = board + ("0" + std::to_string(i)); // adds 0 to the front if i is only one number
        } else {
            board = board + std::to_string(i);
        }
    }
    return board;
}

void printBoard(const string& board, const int& size); 

// This function prints the board in a format that the user can see.
// Two parameters, "board", and "size", board is the string representing board, and size is the size of the board.

void printBoard(const string& board, const int& size) {
    int inc = (2*size - 2); // index of last spot in collum
    for(int i = 0; i <= (((size*size)-1) * 2); i += 2) {
        cout << " " << board[i] << board[i +1];
        if (i == (inc)){ // if in last collum, end line there.
            cout << endl;
            inc += 2*size;
        }
    }
}

string updateBoard(string& board, const int chosenCell, const string& playerSymbol, const int size);

// This function updates the board after the user makes a choice on a cell to mark.
// Four parameters, "board", "chosenCell", "playerSymbol", and "size".
// This function will return the updated string "board", replacing the cell the user chose with the users symbol, but only if that cell is not already occupied.
// This function also will not update the board if the user choice is outside of the range of inputs.

string updateBoard(string& board, const int chosenCell, const string& playerSymbol, const int size){
    string cell;
    // adds 0 to the front if input < 10.
    if (chosenCell < 10) {
        cell = '0' + chosenCell;
    } else {
        cell = chosenCell;
    }

    if ((board[2*chosenCell - 2] == 'S' || board[2*chosenCell - 2] == 'T') || ((size*size) < chosenCell)) { // If space occupied or input out of range, return board with no changes.
        return board;
    } else {
        board.replace((2*chosenCell - 2), 2, playerSymbol);
        return board;
    }
}

bool checkWin(string& board, string& pname, const int size, const char playerSymbol);

// This function checks if there is a condition on the current board that means a win, and returns a boolean value "win".
// Four parameters, "board", "pname", "size", "playerSymbol".
// This function first checks for a row win, then checks for a collum win, then lastly checks for both diagonal and reverse-diagonal wins.
// If at any time a win is found, the function stops and returns (win = true).
// If win not found, returns (win = false).

bool checkWin(string& board, string& pname, const int size, const char playerSymbol) {
    bool win = true;
    int length = (board.length() / 2);
    // check for row win
    for(int i = 0; i < length; i += size) { // for every row
        if (board[2*i] == playerSymbol) { // if first spot in row occupied
            win = true;
            for(int j = i; j < size + i; j += 1) { // for every spot in a row
                if (board[2*j] != playerSymbol) { // if spot not occupied
                    win = false;
                    break;
                }
            }
        } 
        else {
        // If not first num in row occupied, false
            win = false;
        }
        // if win still true, break whole loop
        if (win) {
            break;
        }
    }

    // check for collum win
    if (win == false) {
        for(int i = 0; i < size; i += 1) { // for every collum
            if (board[2*i] == playerSymbol) { // if first spot in collum occupied
                win = true;
                for(int j = i; j < size * size; j += size) { // for every spot in collum
                    if (board[2*j] != playerSymbol) { // if spot not occupied
                        win = false;
                        break;
                    }
                }
            } 
            else {
                // if not first spot in collum occupied, win false
                win = false;
            }
            // if win still true, break whole loop
            if (win) {
                break;
            }
        }
    }

    // check for top-left to bottom-right diagonal

    if (win == false) {
        if (board[0] == playerSymbol) { // if upper left occupied
            win = true;
            for(int i = 0; i < length; i += (size + 1)) { // for every index in diagonal
                if (board[2*i] != playerSymbol) { // if spot not occupied
                    win = false;
                    break;
                }
            }
        } 

    // check for top-right to bottom-left diagonal

        if (board[2*size - 2] == playerSymbol) { // if upper right occupied
            win = true;
            for(int i = (2*size - 2); i <= ((2*size)*(size-1)); i += (2*size - 2)) { // for every index in diagonal
                if (board[i] != playerSymbol) { // if spot not occupied
                    win = false;
                    break;
                }
            }
        } 
    }

    if (win) {
        cout << "Game over! " << pname << " Wins!" << endl;
    }
    return win;
}

bool checkTie(string& board);

// This function checks if there is a tie on the current board.
// One parameter, "board".
// This function will check if every spot on the board is occupied, if so, it will output a gameover message and also return a bool value "tie".

bool checkTie(string& board) {
    bool tie = true;
    int length = (board.length() / 2);

    for(int i = 0; i < length; i++) { // for every index
        if (board[2*i] != 'S' && board[2*i] != 'T') { // if spot not occupied
            tie = false;
            break;
        }
    }
    if (tie == true) {
        cout << "Game Over! It's a tie." << endl;
    }
    return tie;
}

void printGoodbyeMessage();

// No parameters, This function outputs a Goodbye message.

void printGoodbyeMessage() {
    cout << "Goodbye, hope you play again!" << endl;
}

int main()
{
    string p1;
    string p2;
    string p1symbol = "SS";
    string p2symbol = "TT";
    char p1letter = 'S';
    char p2letter = 'T';
    string board;
    string tempboard;
    int p1move;
    int p2move;
    int board_size;
    bool gameover = false;
    

    printWelcomeMessage();

    cout << "Enter the name of Player 1." << endl;
    cin >> p1;
    cout << "Enter the name of Player 2." << endl;
    cin >> p2;

    do { // giant infinite loop that has to be manually stopped by the user quitting the program in the menu by pressing 8 or an input out of range. Causes multiple games to be able to be played.
        displayMenu();
        cin >> board_size;
        
        switch(board_size) // sets board size based on choice
        {
                case 1:
                    board_size = 3;
                    break;
                case 2:
                    board_size = 4;
                    break;
                case 3:
                    board_size = 5;
                    break;
                case 4:
                    board_size = 6;
                    break;
                case 5:
                    board_size = 7;
                    break;
                case 6:
                    board_size = 8;
                    break;
                case 7:
                    board_size = 9;
                    break;
                case 8:
                    exit(0);
                    break;
                default:
                    exit(0);
                    break;
        }

        board = initializeBoard(board_size);

        printBoard(board, board_size);

        do // loop repeats as long as (gameover = false).
        {
            // use variable "tempboard" to check if updateBoard() returns a changed board

            tempboard = board;
            cout << p1 << " (SS), choose a cell:" << endl;
            cin >> p1move;
            board = updateBoard(board, p1move, p1symbol, board_size);

            // if function updateBoard() is called and returns the same board, that means there is an invalid input, in which case we ask for a new input and try again.

            while (tempboard == board) {
                cout << "Invalid input, try again" << endl;
                cin >> p1move;
                tempboard = board;
                board = updateBoard(board, p1move, p1symbol, board_size);
            }

            printBoard(board, board_size);

            gameover = checkWin(board, p1, board_size, p1letter);
            if (gameover) {
                break;
            }

            gameover = checkTie(board);
            if (gameover) {
                break;
            }

            // use variable "tempboard" to check if updateBoard() returns a changed board

            tempboard = board;
            cout << p2 << " (TT), choose a cell:" << endl;
            cin >> p2move;
            board = updateBoard(board, p2move, p2symbol, board_size);

            // if function updateBoard() is called and returns the same board, that means there is an invalid input, in which case we ask for a new input and try again.

            while (tempboard == board) {
                cout << "Space occupied, try again" << endl;
                cin >> p1move;
                tempboard = board;
                board = updateBoard(board, p1move, p1symbol, board_size);
            }

            printBoard(board, board_size);

            gameover = checkWin(board, p2, board_size, p2letter);
            if (gameover) {
                break;
            }

            gameover = checkTie(board);
            if (gameover) {
                break;
            }

        } while (gameover == false);

        printBoard(board, board_size);
        cout << endl;

    } while (true); // giant infinite loop that only stops if the user quits the program in the menu by pressing 8 or an input out of range.
    // causes multiple games to be able to be played.

    return 0;

}