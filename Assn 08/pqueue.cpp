// CSCI 2530
// Assignment: 8
// Author:     Matthew Morgan
// File:       pqueue.cpp
// Tab stops:  4

/* This file provides definitions for the creation of a priority queue,
 * the insertion and removal of data based on priority in those queues,
 * and a function to print the contents of the queue. */

// Inclusion statements
#include <cstdio>
#include <iostream>
#include "pqueue.h"
using namespace std;

/* PQCell is a representation of a single cell in a priority queue.
 * next is a pointer to the subsequent cell in the list.
 * item is the item being stored by the current cell.
 * priority is the priority of the item in the current cell. */

struct PQCell
{
    PQCell* next;
    PQItemType item;
    PQPriorityType priority;
    PQCell(PQCell* n, PQItemType i, PQPriorityType p)
    {
        next = n;
        item = i;
        priority = p;
    }
};

// Function prototypes
void insertCell(PQCell*& p, const PQItemType& item, PQPriorityType pri);

/* isEmpty(q)
 * This function returns true if the priority queue, q, is empty. */

bool isEmpty(const PriorityQueue& q)
{
    return q.start == NULL;
}

/* insert(q, item, pri)
 * This function inserts the 'item' into the priority queue, q, with a priority
 * of pri. */

void insert(PriorityQueue& q, PQItemType item, PQPriorityType pri)
{
    insertCell(q.start, item, pri);
}

/* remove(q, item, pri)
 * This function removes the item with the lowest priority, storing its item
 * and priority into the variables item and pri respectively. */

void remove(PriorityQueue& q, PQItemType& item, PQPriorityType& pri)
{
    if (q.start != NULL)
    {
        item = q.start->item;
        pri = q.start->priority;
        PQCell *newStart = q.start->next;
        delete q.start;
        q.start = newStart;
    }
}

/* printPriorityQueue(q, pi, pp)
 * This function prints the items and priorities stored in a priority queue, q,
 * using the functions pi and pp for each, respectively, or prints that the
 * queue is empty if it's empty. */

void printPriorityQueue(const PriorityQueue& q, ItemPrinter pi,
	PriorityPrinter pp)
{
    if (isEmpty(q))
    {
        cout << "Priority queue is currently empty." << endl;
    }
    else
    {
        cout << "Priority Queue Start " << endl;
        PQCell *nextCell = q.start;
        while (nextCell != NULL)
        {
            cout << "    Priority [ ";
            pp(nextCell->priority);
            cout << " ], Item [ ";
            pi(nextCell->item);
            cout << " ]" << endl;
            nextCell = nextCell->next;
        }
        cout << "Priority Queue End" << endl;
    }
}

/* insertCell(p, item, pri)
 * This function inserts into the linked list, p, an item with priority pri. */

void insertCell(PQCell*& p, const PQItemType& item, PQPriorityType pri)
{
    if (p == NULL)
    {
        p = new PQCell(NULL, item, pri);
    }
    else if (p->priority > pri)
    {
        p = new PQCell(p, item, pri);
    }
    else
    {
        insertCell(p->next, item, pri);
    }
}
