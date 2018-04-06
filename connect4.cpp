#include "connect4.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;

void terminalPlay() {
    
    string player1Name;
    string player2Name;
//    char move = '0';
    string move = "0";
    Board board = getBoard(player1Name, player2Name);
    //
    string player1Move;
    string player2Move;
    board.prettyPrintBoard(cout);
    cout << "\nEnter: the column to move, q to quit, s to save" << endl;
    if(board.toMove() == 2){
        cout << player2Name << " enter your move: ";
    }
    else{
        cout << player1Name << " enter your move: ";
    }
    cin >> move;
    while (move != "Q" && move != "q") {
        if (move == "S" || move == "s") {
            saveBoard(player1Name, player2Name, board);
        }
        //if illegal move
        else if (stoi(move) < 1 || stoi(move) > 7) {
            cout << "ILLEGAL MOVE: Try again" << endl;
        }
        
        //if normal move 
        else{
            Result outcome = board.makeMove(stoi(move));
            if(outcome == Win){
                if(board.toMove() == Player1){
                    cout << "Congratulations " << player2Name << "! You won! " << endl;
                }
                else{
                    cout << "Congratulations " << player1Name << "! You won! " << endl;
                }
                board.prettyPrintBoard(cout);
                break;
            }
            else if(outcome == Draw){
                cout << "Draw!" << endl;
                break;
            }
        }
        board.prettyPrintBoard(cout);
        if(board.toMove() == 1){
            cout <<  player1Name << " enter your move: ";
            cin >> player1Move;
            move = player1Move;
        }
        else{
            cout << player2Name << " enter your move: ";
            cin >> player2Move;
            move = player2Move;
        }
        
        //call make move and based on what that returns
        
        // One of the players gets 4 in a row horizontally, vertically, or diagonally
        
//        cout << //name of the winner << "! You won!" << endl;
        
    // end of while loop
    }
    if(move == "q" || move == "Q"){
        cout << "Thanks for playing!"<< endl;
    }
}

Board getBoard(string &p1, string &p2) {
    string move;
    // ask player if they want to "load game" or "play game"
    cout << "Enter L to load a game, or P to play: " << flush;
    cin >> move;
    
    // user chooses to play the game
    if (move == "P" || move == "p") {
        cout << "Player 1, enter your name: " << flush;
        // players names can be more than one word
        string junk;
        getline(cin, junk);
        getline(cin, p1);
        cout << endl << "Player 2, enter your name: " << flush;
        getline(cin, p2);
        cout << endl;
    }
    else {
        cout << "Enter the filename: " << flush;
        string filename;
        // reading in a file name from user
        cin >> filename;
        // reading input file
        ifstream game;
        string player1, player2, fen;
        // opening the file
        game.open(filename);
        // reading the file
        getline(game, player1);
        getline(game, player2);
        getline(game, fen);
        p1 = player1;
        p2 = player2; 
        Board board(fen);
        // returns the board with moves
        return board;
    }
    return Board();
}

void saveBoard(string p1, string p2, const Board &board) {
    string filename;
    cout << "Enter the filename: " << flush;
    // read in users file
    cin >> filename;
    // writing to a file
    ofstream game(filename);
    game << p1 << endl;
    game << p2 << endl;
    // print the board
    board.printBoard_as_FENstring(game);
}



