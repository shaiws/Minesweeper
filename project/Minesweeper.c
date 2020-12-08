#define _CRT_SECURE_NO_WARNINGS
#define DEBUG 0

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define COLUMNS 8
#define ROWS 8

/*Functions declaration*/
int chooseBoardSize();

void printBoard(char[ROWS][COLUMNS]);

void setMines(char[ROWS][COLUMNS]);

void startGame(char[ROWS][COLUMNS], int);

void printDiscoveredBoard(char[ROWS][COLUMNS]);

int askForCustom();

void main()
{
    srand(time(NULL));
    bool win = false;
    int amountOfMines = 8;
    int boardSize;
    while (boardSize != 8)
    {
        boardSize = chooseBoardSize();
        if (boardSize == -1)
            return;
        else if (boardSize != 8)
            printf("TBD\n");
    }

    char gameBoard[ROWS][COLUMNS] = {
        {48 + 50, 48 + 50, 48 + 50, 48 + 50, 48 + 50, 48 + 50, 48 + 50, 48 + 50},
        {48 + 50, 48 + 50, 48 + 50, 48 + 50, 48 + 50, 48 + 50, 48 + 50, 48 + 50},
        {48 + 50, 48 + 50, 48 + 50, 48 + 50, 48 + 50, 48 + 50, 48 + 50, 48 + 50},
        {48 + 50, 48 + 50, 48 + 50, 48 + 50, 48 + 50, 48 + 50, 48 + 50, 48 + 50},
        {48 + 50, 48 + 50, 48 + 50, 48 + 50, 48 + 50, 48 + 50, 48 + 50, 48 + 50},
        {48 + 50, 48 + 50, 48 + 50, 48 + 50, 48 + 50, 48 + 50, 48 + 50, 48 + 50},
        {48 + 50, 48 + 50, 48 + 50, 48 + 50, 48 + 50, 48 + 50, 48 + 50, 48 + 50},
        {48 + 50, 48 + 50, 48 + 50, 48 + 50, 48 + 50, 48 + 50, 48 + 50, 48 + 50}};
    setMines(gameBoard);
    startGame(gameBoard, amountOfMines);
}

int chooseBoardSize()
{
    int userSizeChoice = 0;
    printf("Welcome to Minesweeper!\n\nPlease choose one of the following options and enter it's number:\n\n1 - for size 8X8\n\n2 - for size 12X12\n\n3 - for size 15X15\n\n4 - for custom size\n\n0 - Exit\n\n");
    scanf("%d", &userSizeChoice);
    switch (userSizeChoice)
    {
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

void setMines(char board[ROWS][COLUMNS])
{
    int randomX = 0, randomY = 0;
    int counter = 0;
    while (counter < 8)
    {
        randomX = rand() % 8;
        randomY = rand() % 8;
        if (board[randomY][randomX] != 'B' + 50)
        {

            board[randomY][randomX] = 'B' + 50;
            counter++; //mine set
            int column, row;

            for (row = randomY - 1; row <= randomY + 1; row++)
            {
                if (row >= 0 && row < ROWS)
                {
                    for (column = randomX - 1; column <= randomX + 1; column++)
                    {
                        if (column >= 0 && column < COLUMNS)
                        {
                            if (board[row][column] != 'B' + 50)
                            {
                                board[row][column]++;
                            }
                        }
                    }
                }
            }
        }
    }
}

void printBoard(char board[ROWS][COLUMNS])
{
    int i, j;
    printf("   |");
    for (i = 0; i < ROWS; i++)
    {
        printf(" %d |", i);
    }
    printf("\n");

    for (i = 0; i < ROWS; i++)
    {
        printf(" %d |", i);
        for (j = 0; j < COLUMNS; j++)
        {
            if (board[i][j] < 98)
                if (board[i][j] == '0')
                    printf("   |");
                else
                    printf(" %c |", board[i][j]);

            else
            {
                printf(" X |");
            }
        }
        printf("\n");
    }
}

void printDiscoveredBoard(char board[ROWS][COLUMNS])
{
    int i, j;
    printf("   |");
    for (i = 0; i < ROWS; i++)
    {
        printf(" %d |", i);
    }
    printf("\n");

    for (i = 0; i < ROWS; i++)
    {
        printf(" %d |", i);
        for (j = 0; j < COLUMNS; j++)
        {
            if (board[i][j] == '0' || board[i][j] == '0' + 50)
                board[i][j] = ' ';
            if (board[i][j] >= 98)
                printf(" %c |", board[i][j] - 50);
            else
                printf(" %c |", board[i][j]);
        }
        printf("\n");
    }
}

void startGame(char gameBoard[ROWS][COLUMNS], int amountOfMines)
{
    bool lose = false, win = 0;
    int x, y, steps = 0;
    printBoard(gameBoard);
    while (!lose && !win)
    {
        if (steps == ROWS * COLUMNS - amountOfMines)
        {
            printf("You win!\n");
            win = true;
            break;
        }

        printf("Please enter your move (ROW COLUMN):\n");
        scanf("%d %d", &y, &x);
        if (y < 0 || x < 0 || y > ROWS || x > COLUMNS || gameBoard[y][x] < 98)
            printf("Invalid move. Try again\n");

        else
        {
            gameBoard[y][x] -= 50;

            if (gameBoard[y][x] == 'B')
            {
                printf("You hit the bomb.\nLoser!\n");
                lose = true;
                printDiscoveredBoard(gameBoard);
            }
            else
            {
                steps++;
                printBoard(gameBoard);
            }
        }
    }
}

//TBD
int askForCustom()
{
    return 10;
}