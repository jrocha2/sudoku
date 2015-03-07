// John Rocha
// CSE 20212 -- Lab 6
// Driver program for SudokuSolver
// main.cpp

#include <iostream>
#include "puzzle.h"
#include "sudokusolver.h"
using namespace std;

int main() {
    SudokuSolver ez("easy.txt"); // file contains puzzle to be solved
    SudokuSolver med("medium.txt");
    SudokuSolver dif("cc1.txt");

    cout << endl << "Easy Puzzle:" << endl;
    ez.display();
    ez.solve();

    cout << endl << endl << "Medium Puzzle:" << endl;
    med.display();
    med.solve();

    cout << endl << endl << "Harder Puzzle:" << endl;
    dif.display();
    dif.solve();

}
