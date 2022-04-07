/* Assignment 2

    This program is a simple lottery game. It runs in an infinite loop so the user can play as many times as they'd like. 
    The user is shown a main menu where the user can do a few simple actions:

        1. Enter their numbers.
            This option allows the user to enter their lotto numbers. These numbers are added to an array and also passed to a 
            seperate function that keeps track of all of the numbers so they can be counted in a later function.

        2. Display their numbers. 
            This option simply displays the most recent set of numbers the user entered.

        3. Sorts the user's most recently entered numbers.
            This option uses the bubble sort algorithm to sort the most recent set of numbers the user entered.
            It sorts the numbers in ascending order and then displays them. 

        4. Compare the user's numbers to a predefined set of winning numbers.
            The program compares the user's entered numbers to a predefinied list of winning numbers and returnrs how many numbers matched. 
            The program then decides what the user has won depending on how many numbers matched.

        5. Displays the frequency of each number entered.
            As mentioned in option 1, the program keeps a running track of all of the numbers entered. This option utilises this to 
            calculate how many times each number was entered and displays it to the user.

        6. Exits the program.
            Exits the program and thanks the user if they have played it. No need to thank them if they haven't played. :)
    
Author: Callum O'Brien C21306503
Date Created: 03/03/22 */

#include <stdio.h>
#include <stdlib.h>

#define size 6
#define freqSize 42

// Each function has a more detailed description where they are declared.
void clrbuffer(void); // Clears the input buffer for input validation.
void mainMenu(void); // Displays the main menu.
int * enterNumbers(void); // Allows the user to enter their Lotto numbers.
int * numbersTotal(int *, int); // Adds the user's numbers to a dynamic array
void bubbleSort(int[]); // Uses the bubble sort algorithm to sort an array.
void swap(int *, int *); // Swaps two integer variables, used for bubbleSort().
void lottoCheck(int[]); // Checks how many of the user's numbers match the winning numbers and returns that value.
void freqCheck(int *, int); // Uses the dynamic array with all of the numbers to count the frequency of each one


int main()
{

    // The program runs infinitely until the user chooses to exit.
    while (1)
    {
        mainMenu();
    } // end while

    return 0;

} // end main()


/*  This function clears the program's input buffer so it does not infinitely loop if a character is 
    entered instead of an integer. 
    This is essential for input validation. */
void clrbuffer(void)
{
    while(getchar() != '\n');
} // end clrbuffer()


/*  This function displays the main menu and asks the user to input what they'd like to do. 
    It has full input validation, ensuring the user only enters the correct value.
    This validated value is then used in a switch statement that calls other functions depending on what
    the user would like to do. */
void mainMenu(void)
{

    int select = 0;
    int *userNumbers;
    int *allNumbers;
    int matches;
    // gamePlayed is static so the program remembers if it's been played during subsequent function calls.
    static int gamePlayed = 0;
    // callCounter is static so the program remembers how many times the user enters a set of numbers. This is used for DMA. 
    static int callCounter = 0;

    printf("\nWelcome to the Lotto game.\nPlease select from any of the options below:\n\n");
    printf("1. Enter your Lotto numbers.\n2. Display the numbers you entered in mode 1.\n");
    printf("3. Sort the numbers you entered.\n4. Check what you have won.\n");
    printf("5. Check how many times each number you entered was entered.\n6. Exit the game.\n\n");

    // The user will only see this message if they have not yet played the game as it is irrelevant afterwards.
    if (gamePlayed == 0)
    {
        printf("\n** Modes 2-5 can only be used when the game has been played at least once. **\n\n");
    } // end if
    
    do
    {

        scanf("%d", &select);
        // The input buffer is cleared to stop the program from infinitely looping in the case of accidental character input.
        clrbuffer();

        if (select < 1 || select > 6) 
        {
            printf("Invalid selection. Please only enter values from 1 to 6.\n");
        } // end if
        
    } while (select < 1 || select > 6) ; // end while

    // Once the user makes their choice, the switch statement calls functions depending on the user's input.
    switch (select)
    {
        
        // Case 1 allows the user to enter their Lotto numbers.
        case 1:
        {
            /*  enterNumbers is called to let the user enter their numbers into a static array. 
                The address of this array is then returned as userNumbers. */
            userNumbers = enterNumbers();

            /*  numbersTotal adds the user's numbers to a dynamic array every time they enter numbers, and then returns the 
                address of this array for use in a later function. */
            allNumbers = numbersTotal(userNumbers, callCounter);

            // Once the game has been played, gamePlayed is set to 1 to unlock options 2-5.
            gamePlayed = 1; 

            // Increments the number of times the user has entered numbers. Used for DMA.
            callCounter++;

            break;
        } // end case 1

        // Case 2 displays the Lotto numbers the user entered in option 1.
        case 2:
        {
            if (gamePlayed == 0)
            {
                printf("\nYou haven't played the game yet. Please select option 1.\n");
            } // end if
            else
            {
                printf("\nThe Lotto numbers you entered are:\n");

                for (int i = 0; i < size; i++)
                {
                    printf("%d ", *(userNumbers + i));
                } // end for

                printf("\n");
            } // end else
            
            break;
        } // end case 2

        // Case 3 uses the bubble sort algorithm to sort the Lotto numbers the user entered.
        case 3:
        {
            if (gamePlayed == 0)
            {
                printf("\nYou haven't played the game yet. Please select option 1.\n");
            } // end if
            else
            {
                printf("\nSorting the entered values...\n");

                bubbleSort(userNumbers);

                printf("The sorted values are: ");

                for (int i = 0; i < size; i++)
                {
                    printf("%d ", *(userNumbers + i));
                } // end for

                printf("\n");
                
            } // end else

            break;
        } // end case 3

        // Case 4 calls the lottoCheck function to tell the user what they've won.
        case 4:
        {
            if (gamePlayed == 0)
            {
                printf("\nYou haven't played the game yet. Please select option 1.\n");
            } // end if
            else
            {
                printf("\nChecking your numbers...\n");

                lottoCheck(userNumbers);
            } // end else

            break;
        } // end case 4

        // Case 5 calls the freqCheck function to tell the user the frequency of all numbers entered.
        case 5:
        {
            if (gamePlayed == 0)
            {
                printf("\nYou haven't played the game yet. Please select option 1.\n");
            } // end if
            else
            {
                /*  freqCheck is called with two parameters. The first is the address of the dynamic array
                    containing all the numbers the user entered. The next parameter is the number of times
                    the user has entered numbers. The importance of this is explained within the function. */
                freqCheck(allNumbers, callCounter);
            } // end else            
            
            break;
        } // end case 5

        // Case 6 exits the game.
        case 6:
        {
            if (gamePlayed != 0)
            {
                printf("\n\nThanks for Playing!");
            } // end if

            printf("\nExiting game...\n\n");

            /*  The exit() function ends the program. It is included in "stdlib.h".
                The parameter tells the OS if the exit was successful or not.
                Using 0 as a parameter tells the OS the program exited intentionally. */
            exit(0); 
        } // end case 6

    } // end switch

} // end mainMenu()


/*  This function allows the user to enter their lotto numbers and checks the numbers are between 1 and 42.
    It also checks if the number being entered has been entered previously. 
    It then returns the address of a static array containing those lotto numbers. */
int * enterNumbers(void)
{

    int select;
    int duplicate;
    // This array is static so its address can be returned and its contents will be accessible.
    static int userNumbers[size]; 

    /*  The array values are reset manually when the function is called as the array is static.
        The values need to be reset in order for the duplicate check to work. */
    for (int i = 0; i < size; i++)
    {
        *(userNumbers + i) = 0;
    } // end for

    printf("\nPlease enter six Lotto numbers between 1 and 42.\n");

    for (int i = 0; i < size; i++)
    {

        do
        {

            /*  select is set to -1 by default as the array containing the user's numbers contains all zeroes until full. 
                Doing this prevents false positives in the duplicate check. */
            select = -1; 
            
            scanf("%d", &select);
            clrbuffer();

            // if the number entered is already in the array, duplicate is set to 1 and select is reset so the while loop doesn't increment.
            for (int i = 0; i < size; i++)
            {
                if (select == *(userNumbers + i))
                {
                    duplicate = 1;
                    // The selection is reset if the number is a duplicate so it is not added to the array.
                    select = -1;
                } // end if
            } // end for
            
            if (duplicate == 1)
            {
                printf("\nYou've already entered that number. Please enter a different one.\n");
                duplicate = 0;
            } // end if
            else if (select < 1 || select > 42)
            {
                printf("\nInvalid selection.\nPlease only enter a value between 1 and 42.\n");
            } // end else if
            else
            {
                *(userNumbers + i) = select;
            } // end else

        } while (select < 1 || select > 42); // end while
        
    } // end for
    
    return userNumbers;

} // end enterNumbers()


/*  This function is called whenever the user enters new numbers. It adds the user's numbers to a dynamic
    array so that it can be used to calculate the frequency of each number.
    Upon the first call, the function creates the dynamic array and add's the user's numbers to it.
    During subsequent calls it extends this array with the extra numbers.
    The address of this dynamic array is then returned. */
int * numbersTotal(int *n, int callCounter)
{
    // firstCall is 1 by default so the function does different things depending on if it is the first function call or not.
    static int firstCall = 1;
    // frequency is static so the contents of the array can be accessed from other functions.
    static int *frequency;
    int extraSize;
    int newSize;
    int sizeOfBlock;
    int noDupeSize;
    int duplicateCount = 0;

    // If it is the first time the user is entering numbers, the dynamic array is created and filled.
    if (firstCall == 1)
    {
        /*  calloc([Number of items], [Size of each element]) 
            I used calloc() as it is simpler than using malloc().*/
        frequency = calloc(size, sizeof(int));

        if (frequency == NULL)
        {
            printf("\nMemory allocation failed. Please try again.\n");
        } // end if
        else
        {
            for (int i = 0; i < size; i++)
            {
                *(frequency + i) = *(n + i);
            } // end for
            
        } // end else
        
        // firstCall is set to 0 so the program knows the function has been called before.
        firstCall = 0; 

    } // end if

    /*  If it is not the first time the user has entered numbers, the dynamic array is reallocated 
        and the new elements are added. */
    else
    {

        /*  The program uses the number of times the function has been called to calculate how much 
            space there needs to be in the dynamic array. */
        extraSize = size * callCounter;

        // This calculates the total size of the new block in bytes.
        newSize = (size + extraSize) * sizeof(int);

        // Reallocates frequency with a size of newSize.
        frequency = realloc(frequency, newSize);

        if (frequency == NULL)
        {
            printf("\nFailed to expand the array. Please try again.\n");
        } // end if
        else
        {
            // The loop begins from the extraSize-th element so the pre-existing elements aren't overwritten.
            for (int i = extraSize; i < size + extraSize; i++)
            {
                // The (i - extraSize)th element is added to account for the loop not starting from 0.
                *(frequency + i) = *(n + (i - extraSize)); 
            } // end for
            
        } // end else
        
    } // end else 

    return frequency;
    
} // end numbersTotal()


/*  This function uses the bubble sort algorithm to sort a list of numbers.
    I used this as bubble sort works well for sorting sets of numbers in many different scenarios and is quite simple. 
    The algorithm compares an element to the one next to it, and swaps them if they are in the wrong order.
    This is repeated for each element until the list is sorted. */
void bubbleSort(int n[])
{

    for (int i = 0; i < size - 1; i++)
    {

        for (int j = 0; j < size - 1; j++)
        {

            if (*(n + j) > *(n + (j + 1)))
            {
                swap(&*(n + j), &*(n + (j + 1)));
            } // end if

        } // end for
        
    } // end for

} // end bubbleSort()


/*  This function uses pass by reference to swap two numbers. It uses pass by reference
    as this will swap the two numbers within the scope of the function it's being called from
    without needing to return anything. */
void swap(int *x, int *y)
{

    int tmp = *x;
    *x = *y;
    *y = tmp;

} // end swap()


/*  This function checks the user's lotto numbers against a predefined array of the winning numbers.
    If the one of the user's numbers matches one of the winning numbers, a counter is incremented.
    The function then determines what the user has won and displays it. */
void lottoCheck(int n[])
{

    int counter = 0;
    // The array containing the winning numbers is constant as these values should never change.
    const int winningNumbers[size] = {1, 3, 5, 7, 9, 11};

    for (int i = 0; i < size; i++)
    {

        // For the selected element, it is compared against all elements of the winningNumbers array. 
        for (int j = 0; j < size; j++)
        {

            if (*(n + i) == *(winningNumbers + j))
            {
                counter++;
            } // end if

        } // end for
        
    } // end for

    // The 'counter' switch displays what the user has won.
    switch (counter)
    {
        case 3:
        {
            printf("\nYou matched 3 numbers! You win a cinema pass!\n");
            break;
        } // end case 3

        case 4:
        {
            printf("\nYou matched 4 numbers! You win a weekend away!\n");
            break;
        } // end case 4

        case 5:
        {
            printf("\nYou matched 5 numbers! You win a new car!\n");
            break;
        } // end case 5

        case 6:
        {
            printf("\nYou matched 6 numbers! You win the jackpot!\n");
            break;
        } // end case 6

        default:
        {
            printf("\nYou didn't win anything, try again!\n");
        } // end default
    } // end switch
    

} // end lottoCheck()


/*  This function checks the frequency of each number the user entered using the dynamic array containing all of the numbers 
    the user has entered. The function creates two additional arrays;
    These arrays use a key-value pair system.
    One array contains 1-42, and the other contains all 0s. If the user's number matches one of the numbers in the first array,
    the matching value of the second array is incremented.
    Finally, a loop is used to print the frequency of values when the frequency is not equal to zero. */
void freqCheck(int *n, int callCounter)
{

    // The program will do different things if it's the first call, so this is static as it needs to be remembered.
    static int firstCall = 1;
    // This is kept static to be more efficient as the contents of this array will never change.
    static int numberList[freqSize];
    int freqCount[freqSize];
    int sizeOfBlock;

    /*  The program uses the number of times the function has been called to calculate how many elements there are in 
        the dynamic array. This is used to know how many times to iterate through the array in the loop. */
    sizeOfBlock = size * callCounter;

    /*  Upon the first call the arrays will be filled with numbers. This is not done upon subsequent calls as the function will 
        not work properly if the values are overwritten. */
    if (firstCall == 1)
    {
        for (int i = 0; i < freqSize; i++)
        {
            // numberList is filled with i + 1 so it contains 1-42 instead of 0-41.
            *(numberList + i) = i + 1;
            *(freqCount + i) = 0;
        } // end for
    } // end if

    /*  The function goes through all of the user's numbers. If the user's number matches one of the numbers from the 
        array containing 1-42, the corresponding value of the second array is incremented. */
    for (int i = 0; i < sizeOfBlock; i++)
    {
        for (int j = 0; j < freqSize; j++)
        {
            if (*(n + i) == *(numberList + j))
            {
                (*(freqCount + j))++;
            } // end if
        } // end for
        
    } // end for

    printf("\nThe frequency of each number was:\n");

    /*  If the value of the second array is greater than zero, the frequency of the corresponding 
        number is displayed. */
    for (int i = 0; i < freqSize; i++)
    {
        if (*(freqCount + i) > 0)
        {
            printf("%d occurred %d time(s).\n", *(numberList + i), *(freqCount + i));
        } // end if 
    } // end for
    
} // end freqCheck()