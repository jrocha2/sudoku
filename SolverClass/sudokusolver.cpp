// John Rocha
// CSE 20212 -- Lab 6
// Implementation of SudokuSolver
// sudokusolver.cpp

#include <iostream>
#include <vector>
#include <fstream>
#include "puzzle.h"
#include "sudokusolver.h"
typedef std::vector<int> Int1D;
typedef std::vector<Int1D> Int2D;
typedef std::vector<Int2D> Int3D;

using namespace std;

SudokuSolver :: SudokuSolver(string filename) : Puzzle<int>(filename), possibles (20,Int2D(20,Int1D(20))){

        // Uses typedef-ed vector spaces and allocates approximately 2X the required space for
        // the 3D possibles vector in order to avoid inconsistent compiler activity that sometimes
        // led to segmentation faults

        // Fills 3D possibles vector representing the possible numbers for each box on the board
        // A value of 1 means that k is a possible fit for box (i,j), otherwise set to 0
        for (int i = 0; i < 10; i++)
            for (int j = 0; j < 10; j++)
                for (int k = 0; k < 10; k++) {
                    if (originalBoard[i][j])
                        possibles[i][j][k] = 0; 
                    else
                        possibles[i][j][k] = 1;
                }

}

int SudokuSolver :: scannerAlg(int row, int column) {

    // Algorithm that checks given box to see if there is only one possible value there
    // and if so it returns that value, otherwise 0
    int numOfPossibles = 9, lastFound = 0;

    for (int i = 1; i <= 9; i++) {
        if (checkValidity(i,row,column)) {     
            possibles[row][column][i] = 0;
            numOfPossibles--;
        }else
            lastFound = i;
    }

    if (numOfPossibles == 1)
        return lastFound;
    else
        return 0;

}

vector<int> SudokuSolver :: singletonAlgRows() {

    // Algorithm that goes through each row determining all the possible values that can go
    // in each unsolved square and adding them to potentialSpots[]. By the end of the row, if
    // there is a value that is only possible in one and none of the other boxes, it should
    // be placed in that box. Also known as solving for "hidden single" or "singleton"
    vector<int> unsolved;
    vector<int> potentialSpots(10,0);
    vector<int> solved(3,0);
    vector<int> :: const_iterator iter;
    int singleton = 0;

    for (int row = 0; row < 9; row++) {         // unsolved contains column # of all unsolved boxes in the row
        
        singleton = 0;
        for (int j = 0; j < 9; j++)         
            if (board[row][j] == 0) 
                unsolved.push_back(j);

        for (iter = unsolved.begin(); iter != unsolved.end(); ++iter) 
            for (int k = 1; k <= 9; k++) 
                if (possibles[row][*iter][k]) // if k possible in (row,*iter), add to potentialSpots
                    potentialSpots[k]++; 
        

        for (int i = 1; i <= 9; i++) {  // iterates through potentialSpots[] to see if hidden single
            if (potentialSpots[i] == 1 && singleton > 0) {
                singleton = 0;
                break;
            }else if (potentialSpots[i] == 1)
                singleton = i;
        }


        if (singleton)          // if hidden single and valid move, add to board as solved
            for (int j = 0; j < 9; j++)
                if (possibles[row][j][singleton] == 1 && !checkValidity(singleton,row,j)) {
                    solved[0] = row;
                    solved[1] = j;
                    solved[2] = singleton;
                    return solved;
                }
        

        unsolved.clear();       // clear unsolved and potentialSpots for evaluation of next row
        fill(potentialSpots.begin(), potentialSpots.end(), 0);
    }

    return solved;      // returns {0 0 0} if nothing found in any row
}

vector<int> SudokuSolver :: singletonAlgCols() {

    // Simiilar to singletonAlgRows() except now going down each column looking for 
    // hidden singles vertically
    vector<int> unsolved;
    vector<int> potentialSpots(10,0);
    vector<int> solved(3,0);
    vector<int> :: const_iterator iter;
    int singleton = 0;

    for (int column = 0; column < 9; column++) {

        singleton = 0;
        for (int i = 0; i < 9; i++)             // unsolved contains row # of all unsolved boxes in column    
            if (board[i][column] == 0) 
                unsolved.push_back(i);

        for (iter = unsolved.begin(); iter != unsolved.end(); ++iter) 
            for (int k = 1; k <= 9; k++) 
                if (possibles[*iter][column][k]) 
                    potentialSpots[k]++;        // if k possible in (*iter,column), add to potentialSpots
                
        for (int i = 1; i <= 9; i++) {  // iterates through potentialSpots to see if hidden single
            if (potentialSpots[i] == 1 && singleton > 0) {
                singleton = 0;
                break;
            }else if (potentialSpots[i] == 1)
                singleton = i;     
        }

        if (singleton)  // if singleton and valid move, then add to board as solved
            for (int i = 0; i < 9; i++)
                if (possibles[i][column][singleton] == 1 && !checkValidity(singleton,i,column)) {
                    solved[0] = i;
                    solved[1] = column;
                    solved[2] = singleton;
                    return solved;
                }

        unsolved.clear();       // reset for evaluation of next column
        fill(potentialSpots.begin(), potentialSpots.end(), 0);
    }

    return solved;      // if no singleton found in any column, returns {0 0 0}
}

vector<int> SudokuSolver :: singletonAlgMiniGrids() {

    // Similar to other singletonAlgs above except it iterates through each 3x3 minigrid looking
    // for hidden singles just within each minigrid. Also no need for previously used unsolved
    // vector because we can deduce the desired row/column by examining where we are in the the main loop
    vector<int> potentialSpots(10,0);
    vector<int> solved(3,0);

    int singleton = 0;

    for (int row = 0; row <= 6; row += 3) {
        for (int column = 0; column <= 6; column += 3) {

            singleton = 0;
            for (int i = row; i < row+3; i++)   // iterates through a minigrid
                for (int j = column; j < column+3; j++) 
                    for (int k = 1; k <= 9; k++) 
                        if (possibles[i][j][k])         // if k possible in (i,j), add to potentialSpots
                            potentialSpots[k]++;

            for (int i = 1; i <= 9; i++) {      // iterates through potentialSpots to see if hidden single
                if (potentialSpots[i] == 1 && singleton > 0) {
                    singleton = 0;
                    break;
                }else if (potentialSpots[i] == 1)
                    singleton = i;
            }
                            
            if (singleton)      // if singleton and it is a valid move, add to board as solved
                for (int i = row; i < row; i++)
                    for (int j = column; j < column; j++)
                        if (possibles[i][j][singleton] == 1 && !checkValidity(singleton,i,j)) {
                           solved[0] = i;
                           solved[1] = j;
                           solved[2] = singleton;
                           return solved;
                        }
            // clear potentialSpots for next minigrid to be evaluated
            fill(potentialSpots.begin(), potentialSpots.end(), 0); 
        }
    }

    return solved;      // if no minigrids contain hidden single, return {0 0 0}
}     

void SudokuSolver :: solve() {
    
    // Implements above algorithms until board solved 
    int solved = 0, wasUpdated = 0, scanSuccess, exhausted;

    while (!solved) {
        wasUpdated = exhausted = 0;     // "updated" tracks that the board is actually being solved

        while (!exhausted) {    // "exhausted" keeps track of when this algorithm is no longer finding anything
            exhausted = 1;
            for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 9; j++) {
                    if (board[i][j] == 0) {     // if unsolved space, tries scanner algorithm
                        scanSuccess = scannerAlg(i,j);
                        if (scanSuccess) {      
                            board[i][j] = scanSuccess;          // if scan found, add it to board, set as solved 
                            setBoxSolved(i,j);                  // concerning possibilities, recognize                       
                            wasUpdated = 1;                     // update, and realize not exhausted yet
                            exhausted = 0;
                        }
                    }
                }
            }
        }

        exhausted = 0;

        while(!exhausted) {
            exhausted = 1;
            vector<int>singleton = singletonAlgRows();          // first tries singletonRows()
            if (singleton[2] == 0)
                singleton = singletonAlgCols();                 // if none, try singletonCols()
            if (singleton[2] == 0)
                singleton = singletonAlgMiniGrids();            // if none, try singletonMiniGrids()
            if (singleton[2] != 0) {                            
                board[singleton[0]][singleton[1]] = singleton[2];       // if singleton found, add to board,
                setBoxSolved(singleton[0],singleton[1]);                // set as solved concerning possibilities,
                wasUpdated = 1;                                         // recognize update, and realize not
                exhausted = 0;                                          // exhausted yet
            }
        }


        if (!wasUpdated) {      // if the board not updated after trying all algorithms, must be solved
                cout << endl << "Solved Board: " << endl;
                display();
                solved = 1; 
        }       

    }
}





void SudokuSolver :: setBoxSolved(int row, int column) {

    // If a box is solved, this function sets all possibilities to 0 so it 
    // is no longer considered when evaluating a subsets possibilities
    for (int k = 0; k < 10; k++)
        possibles[row][column][k] = 0;

}


     


