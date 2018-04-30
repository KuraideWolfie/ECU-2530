// CSCI 2530
// Assignment: 8
// Author:     Matthew Morgan
// File:       trace.h
// Tab stops:  4

#ifndef A8_TRACE
#define A8_TRACE

#include "tree.h"

// Global variables
extern int PROG_TRACE_LEVEL;

// Function prototypes
bool progArgumentCheck(const int argc, char** argv);
void printFrequencies(const int* fArray);
void printFrequencyName(const int chr);
void printFrequencyPadding(const int i);
void printTree(Tree t);
void printCode(const int* fArray, char** code);

#endif
