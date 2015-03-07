// John Rocha
// CSE 20212 -- Lab 5
// Driver program for Puzzle class that prints example board of chars
// and then begins game of 9x9 traditional sudoku
// main.cpp

#include <iostream>
#include "puzzle.h"

int main() {
    Puzzle<char> w("wordoky.txt");
    Puzzle<int> p("sudoku.txt");

    // Display board of chars
    cout << endl << "Example board of chars: " << endl;
    w.display();
    cout << "\t\t------------------------------------" << endl << endl;

    // Display and play on board of ints
    cout << "Let's play Sudoku!" << endl;
    p.play();
}
