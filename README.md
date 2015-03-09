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
The first algorithm I employ is a scanner algorithm that, given a point on the board, checks to see what possible values can be placed there. Then, if it counts that there is only one value able to be placed there, it must be the case that that value belongs there, and so it returns that value.
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
Not only does this algorithm count a space's possibilities, it is also updating the possibles 3D vector by checking a given value's validity with the Puzzle class's *checkValidity()* function. In this way, even if it not able to deduce enough to place a correct value on the board, it at least updates the possibles vector for future reference. 

### Singleton Algorithm (The Hidden Single)
The second algorithm I employ allows the solver to solve medium puzzles as well as some difficult ones. Known to most as finding the "hidden single," this algorithm examines the unsolved boxes in a given row, column, or minigrid. It goes through the possibles 3D vector and counts all of the possibilities in said row/column/minigrid. If there is a possibility that is valid in one box, but not any of the others, then it must be the case that that possibility belongs there. 
````c++
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
````
The above is just a part of the algorithm, but it shows the use of another vector called potentialSpots as well as how this function returns information. PotentialSpots is simply a 10 element vector, and every time an element is possible in a given
row/column/minigrid, it increments potentialSpots at that index. The second for() loop examines this vector, and upon finding that there is one and only one "singleton" or "hidden single," it stores that value. Finally, the algorithm returns its findings in the form of a 3-element vector that contains the solved value as well as the row and column where it belongs. This specific example is taken from the simpleton algorithm that examines each row of the board. In order to solve the harder puzzles, the program also contains two more similar algorithms for examinings down each column and within each minigrid.

###Possible Improvements
Simply applying the two algorithms above is enough to solve easy, medium, and even some hard difficulty sudoku puzzles. However, the most challenging sudoku puzzles employ many different combinations that can only be solved with many algorithms. Of course, there comes a point when programming all of these algorithms becomes inefficient when a computer might be able to solve the puzzle by different methods. The fastest solvers to date employ recursion and/or backtracking that allows the computer to solve the whole puzzle at seemingly one time rather than pick and choose which values it is able to solve. Perhaps I will implement such a function in the future in order to create a program that can solve every sudoku puzzle.

