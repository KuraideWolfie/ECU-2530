// CSCI 2530
// Assignment: 8
// Author:     Matthew Morgan
// File:       huffman.cpp
// Tab stops:  4

/* This file contains functions relating to the generation of a Huffman tree
 * and Huffman code. The tree and code are generated and then written in a
 * binary file, with the tree being based upon character frequencies in data
 * taken from the standard input. The Huffman code is based upon the tree
 * generated from the input. */

// Inclusion statements
#include <cstdio>
#include <iostream>
#include <cstring>
#include "trace.h"
#include "pqueue.h"
#include "binary.h"
using namespace std;

// Function prototypes
bool readFrequencies(int* fArray, const char* fileRead);
void readFrequenciesArray(int* fArray, FILE* f);
Tree huffmanGenerateTree(int* fArray);
void huffmanGenerateQueue(int* fArray, PriorityQueue& q);
void huffmanGenerateCode(Tree t, char** code, const char* pref);
void huffmanTreeFileWrite(BFILE* f, Tree t);
void fileTranslatetoHuffman(FILE* fRead, BFILE* fWrite, char** code);
void fileTranslatetoHuffmanChar(BFILE* fWrite, char** code, int c);
void mainHuffman(int* frequencies, Tree& huffman, char** code);
void mainHuffmanFileWrite(Tree huffman, char** files, char** code);

int main(int argc, char** argv)
{
    if (progArgumentCheck(argc, argv))
	{
		char *files[] = {argv[argc-2], argv[argc-1]}, **code=new char*[256];
		int* frequencies = new int[256];

		for(int i=0; i<256; i++)
		{
			code[i] = NULL;
		}

		if (!readFrequencies(frequencies, files[0]))
		{
		    cout << "PROG: File '" << files[0] << "' can't be opened!" << endl;
		}
		else
		{
		    printFrequencies(frequencies);

		    Tree huffman;
		    mainHuffman(frequencies, huffman, code);
		    mainHuffmanFileWrite(huffman, files, code);
		}

		cout << endl;
	}
	else
	{
		cout << "      huffman [-t] INPUT_FILE OUTPUT_FILE" << endl;
	}

    return 0;
}

/* mainHuffman(frequencies, huffman, code)
 * This function generates a Tree based on character frequencies in the array
 * 'frequencies', storing the Tree into 'huffman.' It also generates a Huffman
 * code for each character with a frequency greater than 0 and stores the code
 * in the string array 'code.' */

void mainHuffman(int* frequencies, Tree& huffman, char** code)
{
    huffman = huffmanGenerateTree(frequencies);
    if (PROG_TRACE_LEVEL)
    {
        cout << "PROG: The huffman tree is: ";
        printTree(huffman);
        cout << endl;
    }

	if (huffman != NULL)
	{
	    huffmanGenerateCode(huffman, code, "");
	}
    printCode(frequencies, code);
}

/* mainHuffmanFileWrite(huffman, files, code)
 * This function assists with writing the Huffman tree contained in 'huffman'
 * and the Huffman code contained in 'code' to a file in the array 'files.'
 * Also written is the translated copy of the initial file the tree and code
 * were based upon. */

void mainHuffmanFileWrite(Tree huffman, char** files, char** code)
{
    FILE* fileRead = fopen(files[0], "r");
    if (fileRead == NULL)
    {
        cout << "PROG: File '" << files[0] << "' can't be opened!" << endl;
    }
    else
    {
        BFILE* fileBinWrite = openBinaryFileWrite(files[1]);
        if (fileBinWrite == NULL)
        {
            cout << "PROG: File '" << files[1] << "' can't be opened!" << endl;
        }
        else
        {
            huffmanTreeFileWrite(fileBinWrite, huffman);
            fileTranslatetoHuffman(fileRead, fileBinWrite, code);
        }
        closeBinaryFileWrite(fileBinWrite);
    }
    fclose(fileRead);
}

/* readFrequencies(fArray, fileRead)
 * This function updates the frequency array, fArray, by reading in all the
 * characters contained in the file 'fileRead'. This function returns true if
 * the frequencies were read in successfully, and returns false if the file
 * 'fileRead' cannot be opened. */

bool readFrequencies(int* fArray, const char* fileRead)
{
    FILE* f = fopen(fileRead, "r");
    if (f == NULL)
    {
        fclose(f);
        return false;
    }
    else
    {
        for(int i=0; i<256; i++)
        {
            fArray[i] = 0;
        }
		
		readFrequenciesArray(fArray, f);
    }
    fclose(f);
    return true;
}

/* readFrequenciesArray(fArray, f)
 * This function helps generate an array of character frequencies as contained
 * in the FILE f. fArray is an array of integers containing the frequencies. */

void readFrequenciesArray(int* fArray, FILE* f)
{
	int cChar;
	do
	{
		cChar = getc(f);
		if (cChar != EOF)
		{
			fArray[cChar]++;
		}
	}
	while (cChar != EOF);
}

/* huffmanGenerateTree(fArray)
 * This function generates a huffman tree from the frequencies listed in
 * the array 'fArray'. It returns the generated Tree.*/

Tree huffmanGenerateTree(int* fArray)
{
    PriorityQueue freq;
    Tree tree[] = {NULL, NULL};
    int pri[] = {0, 0};

    huffmanGenerateQueue(fArray, freq);

    do
    {
        remove(freq, tree[0], pri[0]);
        if (!isEmpty(freq))
        {
            remove(freq, tree[1], pri[1]);
            insert(freq, new Node(tree[0], tree[1]), pri[0] + pri[1]);
        }
    }
    while(!isEmpty(freq));

    return tree[0];
}

/* huffmanGenerateQueue(fArray, q)
 * This function inserts entries into the priority queue, 'q', corresponding to
 * characters and their respective frequencies in the array 'fArray'. */

void huffmanGenerateQueue(int* fArray, PriorityQueue& q)
{
    for(int i=0; i<256; i++)
    {
        if (fArray[i] > 0)
        {
            insert(q, new Node((unsigned char) i), fArray[i]);
        }
    }
}

/* huffmanGenerateCode(t, code, pref)
 * This function generates a Huffman code for the Tree 't', where 'code' is a
 * string array to store the tree's nodes' codes, and 'pref' is the current
 * prefix of the generated code for the tree. */

void huffmanGenerateCode(Tree t, char** code, const char* pref)
{
	if (t->kind == leaf)
	{
	    int cnt;
	    for(cnt=0; pref[cnt]!='\0'; cnt++) {}

	    char* prefFinal = new char[cnt];
	    strcpy(prefFinal, pref);

	    code[(int)((unsigned char)t->ch)] = prefFinal;
	}
	else
	{
	    char* prefNew[] = {new char[8], new char[8]};
	    strcpy(prefNew[0], pref);
	    strcpy(prefNew[1], pref);
	    strcat(prefNew[0], "0");
	    strcat(prefNew[1], "1");

	    huffmanGenerateCode(t->left, code, prefNew[0]);
	    huffmanGenerateCode(t->right, code, prefNew[1]);

	    delete prefNew[0];
		delete prefNew[1];
	}
}

/* huffmanTreeFileWrite(f, t)
 * This function writes the Huffman tree, 't', to the binary file, 'f'. The
 * binary file must be open for reading. */

void huffmanTreeFileWrite(BFILE* f, Tree t)
{
	if (t != NULL)
	{
		if (t->kind == leaf)
		{
		    writeBit(f, 1);
		    writeByte(f, t->ch);
		}
		else
		{
		    writeBit(f, 0);
		    huffmanTreeFileWrite(f, t->left);
		    huffmanTreeFileWrite(f, t->right);
		}
	}
}

/* fileTranslatetoHuffman(fRead, fWrite, code)
 * This function reads characters from the file 'fRead,' translating them with
 * the Huffman code contained in 'code,' storing the result in the file
 * 'fWrite.' */

void fileTranslatetoHuffman(FILE* fRead, BFILE* fWrite, char** code)
{
    for(int c = getc(fRead); c != EOF; c = getc(fRead))
    {
        fileTranslatetoHuffmanChar(fWrite, code, c);
    }
}

/* fileTranslatetoHuffmanChar(fWrite, code, c)
 * This function writes a single character, 'c,' into the binary file 'fWrite'
 * as encrypted by the Huffman code, 'code.' */

void fileTranslatetoHuffmanChar(BFILE* fWrite, char** code, int c)
{
	for(int pos=0; code[c][pos] != '\0'; pos++)
	{
		int bit = (code[c][pos] == '1');
		writeBit(fWrite, bit);
	}
}
