// CSCI 2530
// Assignment: 8
// Author:     Matthew Morgan
// File:       unhuffman.cpp
// Tab stops:  4

/* This file contains functions for the reading of single characters and
 * decoding of a compressed file based upon its Huffman tree and code. */

// Inclusion statements
#include <cstdio>
#include <iostream>
#include <cstring>
#include "trace.h"
#include "binary.h"
#include "pqueue.h"
using namespace std;

// Function prototypes
Tree huffmanTreeFileRead(BFILE* f);
int readCharacter(Tree t, BFILE* f);
void translateFilefromHuffman(Tree t, FILE* fWrite, BFILE* fRead);
void mainHuffmanFileHandle(char** files);

int main(int argc, char** argv)
{
    if (progArgumentCheck(argc, argv))
	{
		char *files[] = {argv[argc-2], argv[argc-1]};
		mainHuffmanFileHandle(files);
		cout << endl;
	}
	else
	{
		cout << "      unhuffman [-t] INPUT_FILE OUTPUT_FILE" << endl;
	}

    return 0;
}

/* huffmanTreeFileRead(f)
 * This function reads a Huffman tree from the binary file 'f'. */

Tree huffmanTreeFileRead(BFILE* f)
{
	int bit = readBit(f);
    if (bit == 1)
    {
        return new Node(readByte(f));
    }
    else if (bit != EOF)
    {
        Tree lT = huffmanTreeFileRead(f);
        Tree rT = huffmanTreeFileRead(f);
        return new Node(lT, rT);
    }
	else
	{
		return NULL;
	}
}

/* readCharacter(t, f)
 * This function reads a single character from the file 'f' and
 * returns the character, as an integer. Each character is derived
 * from its Huffman code by following the Tree 't'. EOF is returned
 * if the end of the file has been reached. */

int readCharacter(Tree t, BFILE* f)
{
	if (t->kind == leaf)
	{
	    return t->ch;
	}
	else
	{
	    int chr = readBit(f);
	    if (chr == EOF)
	    {
	        return EOF;
	    }
	    else if (chr == 1)
	    {
	        return readCharacter(t->right, f);
	    }
	    else
	    {
	        return readCharacter(t->left, f);
	    }
	}
}

/* translateFilefromHuffman(t, fWrite, fRead)
 * This function translates the compressed contents of the file 'fRead'
 * to plain text, storing the result in the file 'fWrite.' The compressed
 * file's contents are translated using the Huffman tree 't'. */

void translateFilefromHuffman(Tree t, FILE* fWrite, BFILE* fRead)
{
	if (t != NULL)
	{
		for(int cChar=readCharacter(t,fRead); cChar!=EOF;
		    cChar=readCharacter(t,fRead))
		{
		    putc(cChar, fWrite);
		}
	}
}

/* mainHuffmanFileHandle(files)
 * This function uses the initial and ending files stored in the array 'files'
 * to assist in decoding a Huffman-encoded set of characters. */

void mainHuffmanFileHandle(char** files)
{
    BFILE* binFileRead = openBinaryFileRead(files[0]);
    if (binFileRead == NULL)
    {
        cout << "PROG: File '" << files[0] << "' can't be opened!" << endl;
    }
    else
    {
        Tree huffman = huffmanTreeFileRead(binFileRead);
        if (PROG_TRACE_LEVEL == 1)
        {
            cout << "The Huffman tree is: ";
            printTree(huffman);
            cout << endl;
        }

        FILE* fileWrite = fopen(files[1], "w");
        if (fileWrite == NULL)
        {
            cout << "PROG: File '" << files[1] << "' can't be opened!" << endl;
        }
        else
        {
            translateFilefromHuffman(huffman, fileWrite, binFileRead);
        }
    }
    closeBinaryFileRead(binFileRead);
}
