// CSCI 2530
// Assignment: 2
// Author:     Matthew Morgan
// File:       hailstone.cpp
// Tab stops:  4

/*
 * This program computes and displays the hailstone sequence beginning with n.
 * The largest term of the sequence and the length of the sequence are printed
 * as well. The program also computes and displays the length and starting term
 * of the longest sequence among those starting with 1, 2, 3, ..., n.
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
        return n / 2;
    }
    else
    {
        return (3 * n) + 1;
    }
}

/*
 * hailstonePrintSequence(n)
 * This function prints all terms of the hailstone sequence beginning with n.
 */
void hailstonePrintSequence(int n)
{
    if (n == 1)
    {
        printf("1");
    }
    else
    {
        printf("%i ", n);
        hailstonePrintSequence(hailstoneNextValue(n));
    }
}

/*
 * hailstoneLength(n)
 * This function computes and returns the length of the hailstone sequence starting with n.
 */
int hailstoneLength(int n)
{
    if (n == 1)
    {
        return 1;
    }
    else
    {
        return 1 + hailstoneLength(hailstoneNextValue(n));
    }
}

/*
 * hailstoneMaxValue(n)
 * This function calculates and returns the highest integer amongst the terms of the hailstone
 * sequence that begins with n.
 */
int hailstoneMaxValue(int n)
{
    if (n == 1)
    {
        // Return 1 since the end of the sequence has been reached
        return 1;
    }
    else
    {
        // Return the greater of the current and next term in the sequence
        int next = hailstoneMaxValue(hailstoneNextValue(n));
        return ((n > next) ? n : next);
    }
}

/*
 * hailstoneLongestSequenceStart(n)
 * This function calculates the starting integer of the longest hailstone sequence amongst those
 * starting with 1 through n and returns it.
 */
int hailstoneLongestSequenceStart(int n)
{
    if (n == 1)
    {
        // Return 1 if the current sequence tested starts with 1
        return 1;
    }
    else
    {
        // Variable declaration
        int index = hailstoneLongestSequenceStart(n-1);
        int length = hailstoneLength(n);
        int lengthNext = hailstoneLength(index);

        if (length < lengthNext)
        {
            return index;
        }
    }
    return n;
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