// John Rocha
// CSE 20212 -- Lab 6
/*
    Interface and implementation for the templated Puzzle class. It can be used to create and 
    manipulate puzzles of various sizes as all the functions except are designed to work with
    any size and both ints and chars
*/
// puzzle.h

#ifndef PUZZLE_H
#define PUZZLE_H

#include<iostream>
#include<vector>
#include<fstream>
#include<cmath>
using namespace std;

template <typename T>
class Puzzle {

    public:
        Puzzle(string filename = "");
        void display();
        void play();

    protected:
        vector<vector <T> > board;      // Board that will change
        vector<vector <T> > originalBoard;      // Holds original values of board
        int checkValidity(T,int,int);
        int checkVertical(T,int,int);
        int checkHorizontal(T,int,int);
        int checkMiniGrid(T,int,int);
        int isGameover();

};

template <typename T>
Puzzle<T> :: Puzzle(string filename) {  // non-default constructor takes filename of board in

    vector<T> tempVec;
    int sizeOfBoard = 0;
    T tempVar;

    ifstream myFile;
    myFile.open(filename.c_str());
    while(!myFile.eof()) {      // Reads and counts entirety of file to determine size
        myFile >> tempVar;
        sizeOfBoard++;
    }
    sizeOfBoard = sqrt(sizeOfBoard);
    myFile.close();

    myFile.open(filename.c_str());
    while(!myFile.eof()) {      // Reads file line by line creating board one vector at a time
        for (int i = 0; i < sizeOfBoard; i++) {
            myFile >> tempVar;
            tempVec.push_back(tempVar);
        }
        board.push_back(tempVec);
        originalBoard.push_back(tempVec);
        tempVec.clear();
    }
}

template <typename T>
void Puzzle<T> :: display() {   // prints board to screen

    int gridSize = sqrt(board[0].size());

    for (int i = 0; i < board[0].size(); i++) {
        cout << "\t\t\t";
        for (int j = 0; j < board[0].size(); j++) {
            if (board[i][j] == '0' || board[i][j] == 0)         // inserts underscores where there are blanks
               cout << "_ ";
            else 
                cout << board[i][j] << " ";
            if ((j+1) % gridSize == 0) 
                cout << "| ";                   // inserts vertical dividers
        }
        if ((i+1) % gridSize == 0) {
            cout << endl << "\t\t\t";
            for(int k = 0; k < 2*board[0].size() + 2*gridSize; k++)
                cout << "=";            // inserts horizontal dividers
        }
        cout <<  endl;
    }
}

template <typename T>
void Puzzle<T> :: play() {      // interactive mode where the user can enter values into board

    int inputRow, inputColumn;
    T input;
    
    while(!isGameover()) {
        cout << endl;
        display();
        cout << endl;

        cout << "Enter the row of the square you would like to change or -1 to quit: ";
        cin >> inputRow;
        if (inputRow == -1) break;      // can exit here without finishing by entering -1
        cout << endl << "Enter the column of the square you would like to change: ";
        cin >> inputColumn;
        cout << endl << "Enter what you would like to place there: ";
        cin >> input;
        
        if (originalBoard[inputRow][inputColumn]) {     // checks that user isn't changing permanent number
            cout << endl << "You cannot change this original board piece!";
            continue;
        }else if (checkValidity(input,inputRow,inputColumn)){   // checks traditional sudoku rules
            cout << endl << "ERROR: This entry is not valid on the current board!";
            continue;
        }else           
            board[inputRow][inputColumn] = input;       // adds piece to board if it is valid

        if (isGameover())       // notifies user on win
            cout << endl << "You successfully solved this puzzle!" << endl;
    }
}
    
template <typename T>
int Puzzle<T> :: checkValidity(T value, int row, int column) {  // function that groups all checks into one

    int validity = checkVertical(value,row,column);
    validity += checkHorizontal(value,row,column);
    validity += checkMiniGrid(value,row,column);
    
    return validity;    // if any of the checks return invalid, this number will be > 0

}

template <typename T>
int Puzzle<T> :: checkVertical(T value, int row, int column) {  // checks all tiles above and below target

    for (int i = 0; i < row; i++)       // all tiles above it making sure value isn't there
        if (board[i][column] == value)
            return 1;
    for (int i = row + 1; i < board[0].size(); i++)     // all tiles below it too
        if (board[i][column] == value)
            return 1;

    return 0;   // return 0 if it is not invalid anywhere
}

template <typename T>
int Puzzle<T> :: checkHorizontal(T value, int row, int column) {        // checks all tiles right and left of target

    for (int j = 0; j < column; j++)    // all tiles left making sure value isn't there
        if (board[row][j] == value) 
            return 1;
    for (int j = column + 1; j < board[0].size(); j++)  // all tiles to the right too
        if (board[row][j] == value)
            return 1;

    return 0;   // return 0 if it is not invalid anywhere
}

template <typename T>
int Puzzle<T> :: checkMiniGrid(T value, int row, int column) {  // checks minigrids to make sure value not already present
    
    int gridSize = sqrt(board[0].size());
    row = row / gridSize;                      // algorithm that determines the start row and column of the minigrid that 
    row *= gridSize;                           // contains the value by using the truncation of integer division
    column = column / gridSize;
    column *= gridSize;

    for (int i = row; i < row + 3; i++)
        for (int j = column; j < column + 3; j++) 
            if (board[i][j] == value)
                return 1;                       // returns 1 if invalid at some point

    return 0;                                   // otherwise return 0 if not invalid anywhere
}

template<typename T>
int Puzzle<T> :: isGameover() {         // simply checks that no blank spaces remain on board because
                                        // the validity checks will have stopped invalid placements
    for(int i = 0; i < board[0].size(); i++) 
        for (int j = 0; j < board[0].size(); j++)
            if (board[i][j] == 0)
                return 0;

    return 1;
}


#endif












