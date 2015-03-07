// John Rocha
// CSE 20212 -- Lab 6
/*
    SudokuSolver interface file that inherits all the properties of the Puzzle class
    in order to access the board and member/helper functions. Adds its own private algorithm
    functions and 3D vector containing a board's possibilities to come together in solve() function
*/
// sudokusolver.h

#ifndef SUDOKUSOLVER_H
#define SUDOKUSOLVER_H

#include <iostream>
#include <vector>
#include <fstream>
#include "puzzle.h"
typedef std::vector<int> Int1D;
typedef std::vector<Int1D> Int2D;
typedef std::vector<Int2D> Int3D;

using namespace std;

class SudokuSolver : public Puzzle<int>{
    
    public:
        SudokuSolver(string filename = "");
        void solve();

    private:
        Int3D possibles;
        void setBoxSolved(int,int);
        int scannerAlg(int,int);
        vector<int> singletonAlgRows();
        vector<int> singletonAlgCols();
        vector<int> singletonAlgMiniGrids();
};

#endif
