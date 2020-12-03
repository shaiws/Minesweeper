/*Shai Michaeli 316221019*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*Stock definitionf for drinks stocks*/
#define STOCK 10
/*Price definition for each drink*/
#define WATER_PRICE 9
#define ORANGE_JUICE_PRICE 8
#define APPLE_JUICE_PRICE 8
#define SPTITE_PRICE 4
#define COLA_PRICE 4

void calculateChange(int totalPaid, int price);

void main() {

    /*Declaring variables*/
    int userChoice = 0, amountOfOnes, amountOfTwos, amountOfFives, amountOfTens, chosenJuicePrice = 0, totalPaid = 0;
    /*Declaring and initiating the juices' stock*/
    int waterStock = STOCK, orangeStock = STOCK, appleStock = STOCK, spriteStock = STOCK, colaStock = STOCK;

    /*In case user did not choose to exit the program, we will proceed the payment proccess*/
    while (userChoice != 6) {
        amountOfOnes = amountOfTwos = amountOfFives = amountOfTens = 0;
        printf("Please choose:\n1. Water.\n2. Orange juice.\n3. Apple juice.\n4. Sprite.\n5. Cola.\n6. exit.\n");
        scanf("%d", &userChoice);
        /*For each choice, initiate the price, and check if the juice is in stock*/
        switch (userChoice) {
            case 1:
                chosenJuicePrice = WATER_PRICE;
                if (waterStock == 0) {
                    printf("There are no bottles of water left\n");
                    continue;
                }
                break;
            case 2:
                chosenJuicePrice = ORANGE_JUICE_PRICE;
                if (orangeStock == 0) {
                    printf("There are no bottles of orange left\n");
                    continue;
                }
                break;
            case 3:
                chosenJuicePrice = APPLE_JUICE_PRICE;
                if (appleStock == 0) {
                    printf("There are no bottles of apple left\n");
                    continue;
                }
                break;
            case 4:
                chosenJuicePrice = SPTITE_PRICE;
                if (spriteStock == 0) {
                    printf("There are no bottles of sprite left\n");
                    continue;
                }
                break;
            case 5:
                chosenJuicePrice = COLA_PRICE;
                if (colaStock == 0) {
                    printf("There are no bottles of cola left\n");
                    continue;
                }
                break;
            case 6:
                printf("Good bye.");
                break;
            default:
                printf("Invalid choice.");
                chosenJuicePrice = 0;
                break;
        }
        /*Print the price, and ask for payment*/
        if (chosenJuicePrice != 0) {
            printf("The price is %d nis.\n", chosenJuicePrice);
            /*Asking for payment until reaches or passes the required price*/
            while (totalPaid < chosenJuicePrice) {
                printf("To pay please enter 4 numbers. The first number is the amount of\n1 nis coins, the second is the amount of 2 nis coins, then 5 and 10\nPlease enter payment (1, 2, 5, 10): ");
                scanf("%d %d %d %d", &amountOfOnes, &amountOfTwos, &amountOfFives, &amountOfTens);
                totalPaid += amountOfOnes + amountOfTwos * 2 + amountOfFives * 5 + amountOfTens * 10;
                if (totalPaid < chosenJuicePrice)
                    printf("The amount does not suffice! Please enter %d more nis.\n", chosenJuicePrice - totalPaid);
                else {
                    if (totalPaid > chosenJuicePrice) {
                        calculateChange(totalPaid, chosenJuicePrice);
                    }
                    printf("Thank you for buying!\n");
                    /*In case payment was successful, decrease the stock of the bought juice*/
                    switch (userChoice) {
                        case 1:
                            waterStock--;
                            break;
                        case 2:
                            orangeStock--;
                            break;
                        case 3:
                            appleStock--;
                            break;
                        case 4:
                            spriteStock--;
                            break;
                        case 5:
                            colaStock--;
                            break;

                        default:
                            break;
                    }

                }
            }
            chosenJuicePrice = 0;
            totalPaid = 0;
        }
    }
}
/**
 * @param totalPaid - the total payment the user paid
 * @param price - the price of the juice the user chose
 * The function gets the totalPaid and the price, and prints the change the user will get back, with the division for per coin type
 */
void calculateChange(int totalPaid, int price) {
    int onesChange = 0, twosChange = 0, fivesChange = 0, tensChange = 0, change = 0;
    change = totalPaid - price;
    printf("Your change is: %d nis.\n", change);
    tensChange = change / 10;
    change = change % 10;
    fivesChange = change / 5;
    change = change % 5;
    twosChange = change / 2;
    change = change % 2;
    onesChange = change / 1;
    printf("You get back (1, 2, 5, 10): %d %d %d %d.\n", onesChange, twosChange, fivesChange, tensChange);
}