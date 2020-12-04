//Shai Michaeli 316221019

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void main()
{
    //Declaring variables
    int userChoice, amountOfOnes = 0, amountOfTwos = 0, amountOfFives = 0, amountOfTens = 0, price = 0, sum = 0, change = 0;
    printf("Please choose:\n1. Water.\n2. Orange juice.\n3. Apple juice.\n4. Sprite.\n5. Cola.\n");
    //Getting input from user for the his choice
    scanf("%d", &userChoice);
    //Setting the price according to the user's choice
    switch (userChoice)
    {
    case 1:
        price = 9;
        break;
    case 2:
        price = 8;
        break;
    case 3:
        price = 8;
        break;
    case 4:
        price = 4;
        break;
    case 5:
        price = 4;
        break;
    default:
        printf("Invalid choice.");
        break;
    }
    //Printing the price for the current choice. And asking user to enter coins
    if (price != 0) {
        printf("The price is %d nis.\nTo pay please enter 4 numbers. The first number is the amount of\n1 nis coins, the second is the amount of 2 nis coins, then 5 and 10\nPlease enter payment (1, 2, 5, 10): ", price);
        scanf("%d %d %d %d", &amountOfOnes, &amountOfTwos, &amountOfFives, &amountOfTens);
        //Calculating the sum of all the entered coins
        sum = amountOfOnes + (amountOfTwos * 2) + (amountOfFives * 5) + (amountOfTens * 10);
        //In case the user entered a sum greater than the required price, prints his change
        if (sum >= price) {
            change = sum - price;
            printf("Your change is: %d nis.\n", change);
        }
        //In case the user entered a sum less than the price, prints error
        else if (sum < price)
            printf("The amount does not suffice!\n");
    }
}