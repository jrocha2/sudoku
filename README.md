# Sudoku
John Rocha   
CSE 20212 -- Lab 5 and Lab 6

## The Puzzle Class 
The included puzzle.h in PuzzleClass is a generic Sudoku puzzle class that generates puzzles 
given an input file containing a puzzle such as the following:

    0 3 2 0 0 8 9 1 4  
    0 0 0 0 0 0 0 0 3  
    0 0 7 1 0 0 0 2 6  
    0 0 8 0 7 6 0 0 0  
    9 2 1 3 0 0 0 8 7  
    0 6 0 0 0 0 4 0 0  
    0 0 0 0 0 0 0 0 0  
    0 0 0 0 4 0 5 0 8  
    8 0 0 6 0 7 0 0 0   

where the 0's represent blank spaces and the rest of the numbers are
displayed on the board. It is templated such that one may create a board of integers or characters.
The board can also vary in size as long as its width and length are both the same perfect square (4x4, 9x9, 16x16, etc).

Included in the class is a play() function that simulates an interactive mode allowing
the user to fill in a Sudoku puzzle while making sure that the user
adheres to the traditional Sudoku rules. In the end, the program will tell the user if they have
successfully completed the puzzle. The included main.cpp and makefile demo a board of chars and then continue on to intiate a game of 9x9 sudoku. 


## The SudokuSolver Class
The SudokuSolver class is designed to solve traditional 9x9 sudoku puzzles containing integers. It is derived from the above Puzzle class and thus inherits access to the game board as well as all of the useful functions that check if a given move is valid. 

### Determining Which Moves Are Possible Where
At the heart of a solver is being able to keep track of which moves are currently possible for every space on the board. Besides solving with recursion, any algorithm that wishes to employ logic requires the ability to access and update such data. I created a 3D vector called possibles for just this purpose. The first two dimensions serve to mirror the game board while the third dimension holds ten integer elements that are either a 0 or 1. Disregarding element 0, the index of this third dimension corresponds to the possibility that that index value is able to be placed in that row and column of the board. 
Examine the following code snippet that can be found throughout the implementation of the class:
````c++
possibles[row][column][k]
````
At all times in the solver program, this points to either a 0 or 1. If it contains a 0, this means that the point *(row,column)* on the board is not able to hold the number *k*. Likewise, if it contains a 1, then *k* is a possible value to fill in that box. By constantly updating this 3D vector with algorithms, the solver seeks to solve the board a square at a time providing more and more data to itself until the entire board is solved.

### Scanner Algorithm
The first algorithm I employ is a scanner algorithm that, given a point on the board, checks to see what possible values can be placed there. Then, if it counts that there is only one value able to be placed there it places it there.
````c++
int SudokuSolver :: scannerAlg(int row, int column) {
 
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
````
