# Sudoku
John Rocha   
CSE 20212 -- Lab 5

### The Puzzle Class 
The included puzzle.h is a generic Sudoku puzzle class that generates puzzles 
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

Included in the class is a play() function that simulates an interactive mode that allows
the user to fill in a Sudoku puzzle while making sure that the user
adheres to the traditional Sudoku rules. In the end, the program will
tell the user whether they solved the puzzle correctly or not. 
