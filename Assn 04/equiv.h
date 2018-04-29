// CSCI 2530
// Assignment: 4
// Author:     Matthew Morgan
// File:       equiv.h
// Tab stops:  4

// These #ifndef and #define lines make it so that, if this file is
// read more than once by the compiler, its body is skipped on all
// but the first time it is read.

#ifndef EQUIV_H
#define EQUIV_H

/* This structure represents an entry in an equivalence relation.
 * boss is the boss of the entry.
 * numConstituents is the number of constituents for the entry. */
struct EquivRelEntry
{
    int boss, numConstituents;
	EquivRelEntry()
	{
		boss = 0;
		numConstituents = 1;
	}
};

// An equivalence relation is an array of the structure EquivRelEntry.
// So ER abbreviates EquivRelEntry*.

typedef EquivRelEntry* ER;

// Public functions
ER   newER      (int n);
void destroyER  (ER e);
bool equivalent (ER e, int x, int y);
void merge      (ER e, int x, int y);

// The following is advertised here solely for debugging. These must
// only be used for debugging.

void showER(ER e, int n);
int  leader(ER e, int x);

#endif
