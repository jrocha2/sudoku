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
