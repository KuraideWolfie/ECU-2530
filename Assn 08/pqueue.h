// CSCI 2530
// Assignment: 8
// Author:     Matthew Morgan
// File:       pqueue.h
// Tab stops:  4

#ifndef PQUEUE_H
#define PQUEUE_H

// Inclusion statements
#include <cstdio>
#include "tree.h"

/* The item being stored in the queue is a Tree. Therefore,
 * PQItemType abbreviates Tree. */

typedef Tree PQItemType;

/* The type of the priority of an item in the queue is an integer.
 * Therefore, PQPriorityType abbreviates int. */

typedef int PQPriorityType;

/* The type ItemPrinter is the type of a function that prints an item. */

typedef void (ItemPrinter)(PQItemType);

/* The type PriorityPrinter is the type of a function that prints a priority. */

typedef void (PriorityPrinter)(PQPriorityType);

/* PQCell is a representation of a single cell in a priority queue. */

struct PQCell;

/* PriorityQueue represents a priority queue that is composed of PQCells.
 * start is a pointer to the first cell of the list, sorted in nondescending
 * order by priority. */

struct PriorityQueue
{
    PQCell* start;
    PriorityQueue()
    {
        start = NULL;
    }
};

// Function prototypes
bool isEmpty(const PriorityQueue& q);
void insert(PriorityQueue& q, PQItemType item, PQPriorityType pri);
void remove(PriorityQueue& q, PQItemType& item, PQPriorityType& pri);

// Debugging function prototypes
void printPriorityQueue(const PriorityQueue& q, ItemPrinter pi,
	PriorityPrinter pp);

#endif
