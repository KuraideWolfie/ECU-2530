// CSCI 2530
// Assignment: 5
// Author:     Matthew Morgan
// File:       testpq.cpp
// Tab stops:  4

/*
 * This file contains the main program to be executed alongside a couple
 * of functions for printing a priority queue's items and priorities.
 */

// Inclusion statements
#include <cstdio>
#include <iostream>
#include "pqueue.h"
using namespace std;

// Type Definitions
typedef const char* CSTRING;

// Function prototypes
void printString(CSTRING s);
void printDouble(double x);
void clearQueue(PriorityQueue pq);
void testQueueEmpty(PriorityQueue pq);

int main()
{
	PriorityQueue pq = PriorityQueue();
	PQItemType item;
	PQPriorityType pri;

	testQueueEmpty(pq);
	insert(pq, "First", 1.4);
	testQueueEmpty(pq);
	insert(pq, "Second", 1.6);
	insert(pq, "Third", 1.5);
	insert(pq, "Fourth", 1.3);
	printPriorityQueue(pq, printString, printDouble);
	remove(pq, item, pri);
	insert(pq, "Fifth", 1.55);
	printPriorityQueue(pq, printString, printDouble);
    clearQueue(pq);
    testQueueEmpty(pq);

    return 0;
}

/* testQueueEmpty(pq)
 * This function tests whether the priority queue, pq, is empty and
 * prints the result. */
void testQueueEmpty(PriorityQueue pq)
{
	cout << "The priority queue is currently "
		 << (isEmpty(pq) ? "empty" : "not empty") << "." << endl;
}

/* clearQueue(pq)
 * This function clears the priority queue, pq, of all items and
 * priorities currently stored. */
void clearQueue(PriorityQueue pq)
{
    PQItemType item;
    PQPriorityType pri;
    while (pq.start != NULL)
    {
        remove(pq, item, pri);
    }
}

/* printString(s)
 * This function prints the specified string, s. */
void printString(CSTRING s)
{
	printf("%s", s);
}

/* printDouble(x)
 * This function prints the double x. */
void printDouble(double x)
{
	printf("%lf", x);
}
