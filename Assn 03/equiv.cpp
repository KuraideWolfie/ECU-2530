// CSCI 2530
// Assignment: 3
// Author:     Matthew Morgan
// File:       equiv.cpp
// Tab stops:  4

/* This file contains functions pertaining to the creation, merging, and
 * destruction of equivalence relations of variable size. Debugging
 * functions are available to display an equivalence relation and its
 * classes to the console screen. */

// Inclusion statements
#include <cstdio>
#include "equiv.h"
using namespace std;

// Function prototypes
void showClass(ER e, int i, int cl);

/* newER(n)
 * This function creates a new equivalence relation with a size of n entries
 * and returns the memory address of the equivalence relation. */
ER newER(int n)
{
    // Create the equivalence relation manager
    ER arr = new EquivRelEntry[n+1];

	// Modify the boss and number of constituents of entries to default values
    for(int i=1; i<n+1; i++)
    {
        arr[i].boss = i;
    }

    return arr;
}

/* leader(e, x)
 * This function returns the leader of x in an equivalence relation e. */
int leader(ER e, int x)
{
    if (e[x].boss == x)
    {
        // Return x because it's the leader
        return x;
    }
    else
    {
		// Modify x's leader and constituent count before returning the leader
        e[x].boss = leader(e, e[x].boss);
        return e[x].boss;
    }
}

/* equivalent(e, x, y)
 * This function returns if x and y are currently in the same equivalence
 * class that is contained in equivalence relation e. */
bool equivalent(ER e, int x, int y)
{
    // Returns whether the leaders are the same
    return (leader(e, x) == leader(e, y));
}

/* merge(e, x, y)
 * Merge the two equivalence classes that contain x and y in the equivalence
 * relation e. */
void merge(ER e, int x, int y)
{
    // Variable declaration (get the leaders)
    int leadX = leader(e, x);
    int leadY = leader(e, y);

	// Perform merge if the leaders of x and y aren't the same
    if (leadX != leadY)
    {
        if (e[leadX].numConstituents > e[leadY].numConstituents)
        {
            // Make y a constituent of x
            e[leadY].boss = leadX;
            e[leadX].numConstituents += e[leadY].numConstituents;
            e[leadY].numConstituents = 0;
        }
        else
        {
            // Make x a constituent of y
            e[leadX].boss = leadY;
            e[leadY].numConstituents += e[leadX].numConstituents;
            e[leadX].numConstituents = 0;
        }
    }
}

/* destroyER(e)
 * This function destroys the equivalence relation e. */
void destroyER(ER e)
{
    delete []e;
}

/* showER(e, n)
 * This function prints the entire contents of the equivalence relation, e, with
 * size n. */
void showER(ER e, int n)
{
    printf("R = ");
    for(int i=1; i<n+1; i++)
    {
        // Print the current equivalency class, i
        showClass(e, n, i);
    }
    printf("\n");
}

/* showClass(e, n, cl)
 * This function prints to the screen all values with the leader cl in the
 * equivalence relation e of size n. */
void showClass(ER e, int n, int cl)
{
    // Boolean variable that specifies if the class is empty
    bool classEmpty = true;

    // Loop through all available values in the relation, e
    for(int i=1; i<n+1; i++)
    {
        // Test if the current value is within the printing equivalency class
        if (leader(e, i) == cl)
        {
            // Print opening bracket if the first value in the class
            // was found and toggle the boolean variable; else print
            // only the discovered value
            if (classEmpty)
            {
                printf("{%i", i);
                classEmpty = false;
            }
            else
            {
                printf(",%i", i);
            }
        }
    }

    // Print closing bracket if at least one value was found to be in
    // the equivalence class
    if (!classEmpty)
    {
        printf("} ");
    }
}
