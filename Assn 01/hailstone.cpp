// CSCI 2530
// Assignment: 1
// Author:     Matthew Morgan
// File:       hailstone.cpp
// Tab stops:  4

/*
 * This program computes and displays the hailstone sequence of an integer taken from the user.
 * It also calculates the longest sequence's length and beginning term from 1 to the entered
 * integer by the user.
 */

// Inclusion statements
#include <cstdio>
using namespace std;

// Function prototypes
void hailstonePrintSequence(int n);
int hailstoneNextValue(int n);
int hailstoneLength(int n);
int hailstoneMaxValue(int n);
int hailstoneLongestSequenceLength(int n);
int hailstoneLongestSequenceStart(int n);

int main()
{
    // Variable declaration for user input and longest sequence start term
    int userInput;

    // Prompt user for integer input
    printf("What number shall I start with? ");
    scanf("%i", &userInput);

    // Print the hailstone sequence
    printf("The hailstone sequence starting at %i is:\n", userInput);
    hailstonePrintSequence(userInput);
    printf("\n");

    // Print the length and largest integer of the sequence
    printf("The length of the sequence is %i.\n", hailstoneLength(userInput));
    printf("The largest integer of the sequence is %i.\n", hailstoneMaxValue(userInput));

    // Calculate which integer (from 1 to n) is longest; print the starting term and length
    printf("The longest hailstone sequence starting with a number up to %i has length %i.\n",
           userInput, hailstoneLongestSequenceLength(userInput));
    printf("The longest hailstone sequence starting with a number up to %i starts with %i.\n",
           userInput, hailstoneLongestSequenceStart(userInput));

    return 0;
}

/*
 * hailstoneNextValue(n)
 * This function computes and returns the subsequent integer in the hailstone sequence starting
 * with n. The parameter n must be greater than 1.
 */
int hailstoneNextValue(int n)
{
    // Calculate if the current integer is even
    if (n % 2 == 0)
    {
        // n is even; calculate the next term
        return n / 2;
    }
    else
    {
        // n is odd; calculate the next term
        return (3 * n) + 1;
    }
}

/*
 * hailstonePrintSequence(n)
 * This function computes and prints every term of the hailstone sequence that begins with n.
 */
void hailstonePrintSequence(int n)
{
    // Variable declaration
    int cHailstoneNum = n;

    // Loop calculation of hailstone integers until the current hailstone
    // number is equivalent to 1. Print each to the screen.
    while (cHailstoneNum != 1)
    {
        printf("%i ", cHailstoneNum);
        cHailstoneNum = hailstoneNextValue(cHailstoneNum);
    }

    // Print the last hailstone integer (1) to the screen.
    printf("%i", cHailstoneNum);
}

/*
 * hailstoneLength(n)
 * This function computes and returns the length of the hailstone sequence starting with n.
 */
int hailstoneLength(int n)
{
    // Variable declaration - current term and current length
    int cHailstoneNum = n;
    int cHailstoneLength = 1;

    // Loop calculation of hailstone integers until the current hailstone
    // number is equivalent to 1.
    while (cHailstoneNum != 1)
    {
        cHailstoneLength++;
        cHailstoneNum = hailstoneNextValue(cHailstoneNum);
    }

    // Return the length of the sequence
    return cHailstoneLength;
}

/*
 * hailstoneMaxValue(n)
 * This function calculates and returns the highest integer amongst the terms of the hailstone
 * sequence that begins with n.
 */
int hailstoneMaxValue(int n)
{
    // Variable declaration - current term and current largest term
    int cHailstoneNum = n;
    int cHailstoneLarge = n;

    // Loop calculation of hailstone integers until the current hailstone
    // integer is equivalent to 1.
    while (cHailstoneNum != 1)
    {
        // Calculate the next term in the sequence
        cHailstoneNum = hailstoneNextValue(cHailstoneNum);
        if (cHailstoneNum > cHailstoneLarge)
        {
            // Store the term if it is the largest term
            cHailstoneLarge = cHailstoneNum;
        }
    }

    // Return the largest term of the sequence
    return cHailstoneLarge;
}

/*
 * hailstoneLongestSequenceStart(n)
 * This function calculates the starting integer of the longest hailstone sequence amongst those
 * starting with 1 through n and returns it.
 */
int hailstoneLongestSequenceStart(int n)
{
    // Variable declaration - current longest sequence starting term
    int longestTerm = 1;

    // Loop through all hailstone sequences from 1 to n to compute which
    // has the longest length.
    for (int i = 1; i <= n; i++)
    {
        if (hailstoneLength(i) > hailstoneLength(longestTerm))
        {
            longestTerm = i;
        }
    }

    // Return starting term for the longest sequence
    return longestTerm;
}

/*
 * hailstoneLongestSequenceLength(n)
 * This function calculates the length of the longest hailstone sequence amongst those that begin
 * with the term 1 through n.
 */
int hailstoneLongestSequenceLength(int n)
{
    return hailstoneLength(hailstoneLongestSequenceStart(n));
}
