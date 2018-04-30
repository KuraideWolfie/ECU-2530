// CSCI 2530
// Assignment: 8
// Author:     Matthew Morgan
// File:       trace.cpp
// Tab stops:  4

/* This file contains functions in relation to the printing of character
 * frequencies or the characters themselves. Functions are also available for
 * the printing of a Huffman tree and Huffman code. */

// Inclusion statements
#include <cstring>
#include <cctype>
#include <cstdio>
#include <iostream>
#include "trace.h"
using namespace std;

// Global variables
int PROG_TRACE_LEVEL = 0;

/* progArgumentCheck(argc, argv)
 * This function checks for any valid arguments submitted via the command line.
 * Arguments to be checked are stored in argv, and the number of arguments to
 * be checked is argc. This function returns true if enough arguments that are
 * valid are provided, or false otherwise. */

bool progArgumentCheck(const int argc, char** argv)
{
	if (argc >= 3)
	{
		for(int i=1; i<argc; i++)
		{
		    char* cArg = argv[i];
		    if (strcmp(cArg, "-t")==0)
		    {
		        PROG_TRACE_LEVEL = 1;
		    }
		}
		return true;
	}
	
	cout << "PROG: Not enough arguments supplied to function." << endl;
	return false;
}

/* printFrequencies(fArray)
 * This function prints all character frequencies that are greater than 0
 * that are contained in the array fArray. */

void printFrequencies(const int* fArray)
{
    if (PROG_TRACE_LEVEL == 1)
    {
        cout << "PROG: The frequencies read are as follows:" << endl;
        for(int i=0; i<256; i++)
        {
            if (fArray[i] > 0)
            {
                cout << "      ";
                printFrequencyName(i);
                printFrequencyPadding(i);
                cout << fArray[i] << endl;
            }
        }
    }
}

/* printFrequencyPadding(i)
 * This function prints appropriate spacial padding for an unsigned character
 * with a value of i in special cases. */

void printFrequencyPadding(const int i)
{
    unsigned char chr = (unsigned char) i;
    cout << ", ";
    if (isprint(chr) && (chr != ' '))
    {
        cout << "    ";
    }
    else
    {
        if (chr == '\t')
        {
            cout << "  ";
        }
        else if ((chr != '\n') && (chr != ' '))
        {
            if (i < 10)
            {
                cout << "   ";
            }
            else if (i < 100)
            {
                cout << "  ";
            }
            else
            {
                cout << " ";
            }
        }
    }
}

/* printFrequencyName(chr)
 * This function prints the name of a character with an unsigned value
 * of chr. */

void printFrequencyName(const int chr)
{
    unsigned char c = (unsigned char)chr;
    if (isprint(chr))
    {
        if (c == ' ')
        {
            cout << "SPACE";
        }
		else
        {
            cout << c;
        }
    }
    else
    {
        if (c == '\n')
        {
            cout << "NEWLN";
        }
        else if (c == '\t')
        {
            cout << "TAB";
        }
        else
        {
            printf("\\%i", chr);
        }
    }
}

/* printTree(t)
 * This function prints the Tree, t. */

void printTree(Tree t)
{
    if (PROG_TRACE_LEVEL == 1)
    {
        if (t != NULL)
        {
            if (t->kind == leaf)
            {
                printFrequencyName(t->ch);
            }
            else
            {
                cout << "(";
                printTree(t->left);
                cout << ",";
                printTree(t->right);
                cout << ")";
            }
        }
    }
}

/* printCode(fArray, code)
 * This function prints every character's representation in the Huffman code
 * array, 'code', if the frequency of that character as contained in the array
 * 'fArray' is higher than 0. */

void printCode(const int* fArray, char** code)
{
    if (PROG_TRACE_LEVEL == 1)
    {
        cout << "PROG: The huffman code generated is as follows:" << endl;
        for(int i=0; i<256; i++)
        {
            if (fArray[i] > 0)
            {
                cout << "      ";
                printFrequencyName(i);
                printFrequencyPadding(i);
                cout << code[i] << endl;
            }
        }
    }
}
