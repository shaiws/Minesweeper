/*Shai Michaeli - 316221019*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXSIZE 23 /*As mentioned in the project documentation, the game board will not exceed from 23x23*/

/*Functions declaration*/
int chooseBoardSize();
void printBoard(int, int, char[MAXSIZE][MAXSIZE]);
void setMines(int, int, char[MAXSIZE][MAXSIZE], int);
void startGame(int, int, char[MAXSIZE][MAXSIZE], int);
void initBoard(int, int, char[MAXSIZE][MAXSIZE]);
void printDiscoveredBoard(int, int, char[MAXSIZE][MAXSIZE]);
int autoTurn(int, int, int, int, char[MAXSIZE][MAXSIZE]);
int askForCustom();

void main() {
    srand(time(NULL));                    /*use of the computer's internal clock to control the choice of the seed.*/
    int amountOfMines = 0;                /*Amount of mines that will be setup on the board.*/
    int boardSize, rows = 0, columns = 0; /*The board size is the user's choice, and according to this, the board rows and columns will be set*/
    while (boardSize != 8)                /*As the current phase of the project is part A, we won't handle any other choice but 8x8*/
    {
        boardSize = chooseBoardSize();
        rows = columns = 8;
        amountOfMines = 8;
        if (boardSize == -1)
            return;
        else if (boardSize != 8)
            printf("TBD\n");
    }

    char gameBoard[rows][columns]; /*The game board*/
    initBoard(rows, columns, gameBoard);
    setMines(rows, columns, gameBoard, amountOfMines);
    startGame(rows, columns, gameBoard, amountOfMines);
}

/**
 * The function asks the user to choose the game board size. (Currently only 8x8 is supported)
 * @return The board size according to the user's choice
 */
int chooseBoardSize() {
    int userSizeChoice = 0;
    printf("Welcome to Minesweeper!\n\nPlease choose one of the following options and enter it's number:\n\n1 - for size 8X8\n\n2 - for size 12X12\n\n3 - for size 15X15\n\n4 - for custom size\n\n0 - Exit\n\n");
    scanf("%d", &userSizeChoice);
    switch (userSizeChoice) {
        case 0:
            userSizeChoice = -1;
            break;
        case 1:
            userSizeChoice = 8;
            break;
        case 2:
            userSizeChoice = 12;
            break;
        case 3:
            userSizeChoice = 15;
            break;
        case 4:
            userSizeChoice = askForCustom();
            break;
        default:
            printf("Invalid choice\n");
    }
    return userSizeChoice;
}

/**
 * The function gets the game board and initiating every cell with 'c' (int value is 99) which indicates the cell is not opened (c - for closed)
 * @param rows - The number of rows of the board
 * @param columns - The number of columns of the board
 * @param gameBoard - The game board
 */
void initBoard(int rows, int columns, char gameBoard[][columns]) {
    int i, j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < columns; j++) {
            gameBoard[i][j] = 'c';
        }
    }
}

/**
 * The function gets the game board and an amount of mines it should set on the board randomly.
 * Then the function adds 1 to the surrounding cells of the mines, only if it is not a mine itself.
 *
 * @param rows - The number of rows of the board
 * @param columns - The number of columns of the board
 * @param gameBoard - The game board
 * @param amountOfMines - The amount of mines the function will set on the game board
 */
void setMines(int rows, int columns, char gameBoard[][columns], int amountOfMines) {
    int randomX = 0, randomY = 0;
    int counter = 0;
    while (counter < amountOfMines) {
        randomX = rand() % columns;                    /*A random number between 0 to columns number*/
        randomY = rand() % rows;                       /*A random number between 0 to rows number*/
        if (gameBoard[randomY][randomX] != 'B' + 51) { /*Check if the current cell is not already a mine (we will use the 51 value to convert the 'c' value to the number of adjacent mines, as the difference between 'c' to '0' is 51*/
            gameBoard[randomY][randomX] = 'B' + 51;
            counter++; /*Mine set*/
            int column, row;
            /*The following will add 1 to the adjacent cells of the current mine*/
            for (row = randomY - 1; row <= randomY + 1; row++) {
                if (row >= 0 && row < rows) {
                    for (column = randomX - 1; column <= randomX + 1; column++) {
                        if (column >= 0 && column < columns) {
                            if (gameBoard[row][column] != 'B' + 51) {
                                gameBoard[row][column]++;
                            }
                        }
                    }
                }
            }
        }
    }
}

/**
 * The function prints the game board in its current state
 * @param rows - The number of rows of the board
 * @param columns - The number of columns of the board
 * @param gameBoard - The game board
 */
void printBoard(int rows, int columns, char gameBoard[][columns]) {
    int i, j;
    printf("   |");
    for (i = 0; i < columns; i++) {
        printf(" %d |", i); /*prints row of numbers from 0 to number of columns*/
    }
    printf("\n");
    for (i = 0; i < rows; i++) {
        printf(" %d |", i);
        for (j = 0; j < columns; j++) {
            if (gameBoard[i][j] < 'c')      /*if the cell is not closed*/
                if (gameBoard[i][j] == '0') /*if the cell's value is '0' will prints a ' ' (space)*/
                    printf("   |");
                else
                    printf(" %c |", gameBoard[i][j]); /*else will print the value of the cell (number of surrounding mines*/
            else {
                printf(" X |"); /*if cell is still closed, prints X*/
            }
        }
        printf("\n");
    }
}

/**
 * The function prints the game board as all the cells discovered
 * @param rows - The number of rows of the board
 * @param columns - The number of columns of the board
 * @param gameBoard - The game board
 */
void printDiscoveredBoard(int rows, int columns, char gameBoard[][columns]) {
    int i, j;
    printf("   |");
    for (i = 0; i < columns; i++) {
        printf(" %d |", i); /*prints row of numbers from 0 to number of columns*/
    }
    printf("\n");

    for (i = 0; i < rows; i++) {
        printf(" %d |", i);
        for (j = 0; j < columns; j++) {
            if (gameBoard[i][j] == '0' || gameBoard[i][j] == '0' + 51) /*if the cell value is '0' (opened) or '0' (closed) will print ' ' (space)*/
                gameBoard[i][j] = ' ';
            else if (gameBoard[i][j] == 'c') /*if the cell is not yet opened, will print the cell's value as it was opened*/
                printf(" %c |", gameBoard[i][j] - 51);
            else
                printf(" %c |", gameBoard[i][j]); /*prints opened cell's value'*/
        }
        printf("\n");
    }
}

/**
 * This function handles the game.
 * @param rows - The number of rows of the board
 * @param columns - The number of columns of the board
 * @param gameBoard - The game board
 * @param amountOfMines
 */
void startGame(int rows, int columns, char gameBoard[][columns], int amountOfMines) {
    bool lose = false, win = false; /*Boolean variables to determine if the user yet won or lost the game*/
    int xCoordinate, yCoordinate;   /*The user's choice*/
    int steps = 0;                  /*Counter for the user's moves*/
    printBoard(rows, columns, gameBoard);
    while (!lose && !win) /*Will keep running unless user lost or won*/
    {
        if (steps == (rows * columns) - amountOfMines) /*If the user did enough moves (all the board cells minus the amount of mines) without opening a mine, the user won*/
        {
            printf("You win!\n");
            win = true;
            break;
        }

        printf("Please enter your move (ROW COLUMN):\n");
        scanf("%d %d", &yCoordinate,
              &xCoordinate); /*Asking the user for a move, and make all the necessary validation*/
        if (yCoordinate == -1) {
            if (xCoordinate < 0)
                printf("Invalid move\n");
            else {
                steps += autoTurn(xCoordinate, steps, rows, columns, gameBoard); /*Adding the auto moves to the moves the player played*/
                printBoard(rows, columns, gameBoard);
            }
        } else if (yCoordinate < 0 || xCoordinate < 0 || yCoordinate > rows || xCoordinate > columns ||
                   gameBoard[yCoordinate][xCoordinate] < 'c')
            printf("Invalid move. Try again\n");

        else /*In case of a valid move*/
        {
            gameBoard[yCoordinate][xCoordinate] -= 51; /*Discover the selected cell*/

            if (gameBoard[yCoordinate][xCoordinate] == 'B') /*The user hit a mine*/
            {
                printf("You hit a mine.\nLoser!\n");
                lose = true;
                printDiscoveredBoard(rows, columns, gameBoard);
            } else {
                steps++;
                printBoard(rows, columns, gameBoard);
            }
        }
    }
}

/**
 *The function will discover an amount of closed cells in the board (excluding the mines cells)
 * @param amountOfCellsToOpen - The number of cells the player asked to automatically discover
 * @param steps - The number of steps the player made till now
 * @param rows - The number of rows of the board
 * @param columns - The number of columns of the board
 * @param gameBoard - The game board
 * @return The overall moves the player did plus the moves the the function did
 */
int autoTurn(int amountOfCellsToOpen, int steps, int rows, int columns, char gameBoard[][columns]) {
    int counter = 0;
    int i, j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < columns; j++) {
            if (counter < amountOfCellsToOpen) {
                if (gameBoard[i][j] >= 'c' && gameBoard[i][j] - 51 != 'B') {
                    gameBoard[i][j] -= 51;
                    counter++;
                    steps++;
                }
            }
            if (i + 1 == rows && j + 1 == columns) {
                counter = amountOfCellsToOpen;
            }
        }
    }

    return steps;
}

/*TBD in part B*/
int askForCustom() {
    return 10;
}