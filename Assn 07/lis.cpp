// CSCI 2530
// Assignment: 7
// Author:     Matthew Morgan
// File:       lis.cpp
// Tab stops:  4

/*
 * This file contains functions pertaining to the generation of a book of names
 * and elevations corresponding to an array of mountains. Functions are also
 * available for the generation of best increasing sublists and manipulation of
 * ListCell reference counts therein. Debugging functions are also available for
 * printing the contents of a book of mountains or printing one or all sublists.
 */

// Inclusion statements
#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;

// Global constants, variables
const int MAX_MOUNTAINS = 100;
const int MAX_NAME_CHRS = 50;
bool PROG_TRACE = false;
bool PROG_TOGG_CELLDELETION = true;
bool PROG_TOGG_CELLREFERENCE = false;

// Structure prototypes
struct Mountain;
struct MountainBook;
struct ListCell;
struct AllBis;

/* Book represents a pointer to a MountainBook, and therefore abbreviates
 * MountainBook*. */

typedef MountainBook* Book;

/* A SubList is essentially a pointer to a ListCell. Therefore, it abbreviates
 * ListCell*. */

typedef ListCell* SubList;

// Function prototypes
Book mountainBookCreate();
void mountainBookInsert(Book& book, char* mntName, int mntElevation);
void mountainBookPrint(Book& book);
bool mountainShorter(Book& book, int mntA, int mntB);
AllBis* bisGenerate(Book book);
void sublistExtend(AllBis* bis, int list, int prefix);
int  sublistExtensionIndex(AllBis* bis, int prefix, Book book);
void sublistPrint(SubList list);
void sublistPrintAll(AllBis* bis);
void cellReferenceBump(ListCell* cell);
void cellReferenceDrop(ListCell* cell);
void setList(ListCell*& cellA, ListCell* cellB);
void mountainPrintAll(AllBis* bis, Book book);
void mountainPrintSingle(ListCell* cell, Book book);

/* Mountain represents a single mountain entry in a MountainBook.
 * name is the name of the mountain.
 * elevation is the height of the mountain from base to peak. */

struct Mountain
{
    const char* name;
    int elevation;
    Mountain()
    {
        name = "";
        elevation = 0;
    }
};

/* MountainBook represents a collection of mountains' names and elevations.
 * mountains is the array containing information for the book's mountains.
 * mountainCount is the current number of mountains contained in the book. */

struct MountainBook
{
    int mountainCount;
    Mountain* mountains;
    MountainBook()
    {
        mountains = new Mountain[MAX_MOUNTAINS];
        mountainCount = 0;
    }
};

/* ListCell is a single cell in a linked list.
 * next is a pointer to the next cell in the list.
 * item is a piece of data stored by the ListCell.
 * references is the number of references to the ListCell. */

struct ListCell
{
    ListCell* next;
    int item, references;
    ListCell(int x, ListCell* nxt)
    {
		next = NULL;
		references = 0;
		setList(next, nxt);
        item = x;
    }
};

/* AllBis is a collection of best increasing sublists.
 * lists is an array holding pointers to the beginning of each sublist.
 * listCount is the number of lists in the collection of lists.
 * listLongest is the length of the current, longest sublist. */

struct AllBis
{
    SubList* lists;
    int listCount, listLongest;
    AllBis(int cnt)
    {
		listLongest = 0;
        listCount = cnt+1;
        lists = new SubList[listCount];
		for(int i=0; i<listCount; i++)
		{
			lists[i] = NULL;
		}
    }
};

/* progArgumentCheck(argc, argv)
 * This function checks for any valid arguments submitted via the command line.
 * Arguments to be checked are stored in argv, and the number of arguments to
 * be checked is argc. This function returns false if an invalid argument has
 * been detected, or true if all arguments are valid. */

bool progArgumentCheck(const int argc, char** argv)
{
    for(int i=1; i<argc; i++)
    {
        char* cArg = argv[i];
        if (strcmp(cArg, "-t")==0)
        {
            PROG_TRACE = true;
			PROG_TOGG_CELLREFERENCE = true;
			PROG_TOGG_CELLDELETION = false;
        }
        else
        {
            cout << "usage: lis [-t]" << endl;
            return false;
        }
    }
    return true;
}

int main(int argc, char** argv)
{
    if (progArgumentCheck(argc, argv))
    {
		Book book = mountainBookCreate();
		mountainBookPrint(book);
		AllBis* lst = bisGenerate(book);
		cout << endl;
		mountainPrintAll(lst, book);
		if (PROG_TRACE)
		{
			cout << endl;
			sublistPrintAll(lst);
		}
	}
    return 0;
}

/* mountainBookCreate()
 * This function generates a Book containing mountain names and elevations from
 * the standard input. It returns a pointer to the generated Book. */

Book mountainBookCreate()
{
    Book book = new MountainBook;

	do
	{
		char* name = new char[MAX_NAME_CHRS];
		int height;
		cin >> name >> height;
		mountainBookInsert(book, name, height);
	}
	while(!feof(stdin) && book->mountainCount<MAX_MOUNTAINS);

    return book;
}

/* mountainBookInsert(book, mntName, mntElevation)
 * This function inserts a mountain with the name 'mntName' and elevation
 * 'mntElevation' into the Book 'book.' 'mntName' cannot be an empty string,
 * and 'mntElevation' must be greater than or equivalent to 0. */

void mountainBookInsert(Book& book, char* mntName, int mntElevation)
{
	if (strcmp(mntName,"")!=0 && mntElevation>=0)
	{
		if (PROG_TRACE)
		{
			cout << "PROG: Inserting mountain. Index [" << book->mountainCount
				 << "], parameters: [" << mntName << "," << mntElevation
				 << "]." << endl;
		}

		int cur = book->mountainCount;
		book->mountains[cur].name = mntName;
		book->mountains[cur].elevation = mntElevation;
		book->mountainCount++;
	}
}

/* mountainBookPrint(book)
 * This function prints the list of mountains and their corresponding elevations
 * as contained in the Book 'book.' */

void mountainBookPrint(Book& book)
{
    int cnt = book->mountainCount;
    cout << "This book contains " << cnt << " mountain(s)." << endl;

    for(int i=0; i<cnt; i++)
    {
		printf("%3i. Height %5i, %s\n", i+1, book->mountains[i].elevation,
			    book->mountains[i].name);
    }
}

/* mountainShorter(book, mntA, mntB)
 * This function returns true if Mountain 'mntA' is shorter than Mountain 'mntB'
 * in the Book 'book,' or false otherwise. */

bool mountainShorter(Book& book, int mntA, int mntB)
{
	return book->mountains[mntA].elevation
		   < book->mountains[mntB].elevation;
}

/* bisGenerate(book)
 * Utilizing the list of mountains contained within the Book 'book,' this
 * function generates a collection of best increasing sublists. It returns
 * a pointer to the generated AllBis. */

AllBis* bisGenerate(Book book)
{
    AllBis* lst = new AllBis(book->mountainCount);

    for(int i=0; i<book->mountainCount; i++)
    {
        sublistExtend(lst, sublistExtensionIndex(lst, i, book), i);
    }

    return lst;
}

/* sublistPrintAll(bis)
 * This function prints all sublists contained within AllBis 'bis'. */

void sublistPrintAll(AllBis* bis)
{
    cout << "PROG: Printing sublists of length 0 to "
		 << bis->listLongest << "." << endl;

    for(int i=0; i<bis->listLongest+1; i++)
    {
		printf("      Length %3i: ", i);
        sublistPrint(bis->lists[i]);
    }
}

/* sublistPrint(list)
 * This function prints a single SubList, 'list', from beginning to end. */

void sublistPrint(SubList list)
{
    bool useComma = false;
    cout << "{";

	while(list != NULL)
	{
		if (!useComma)
		{
			useComma = true;
		}
		else
		{
			cout << ", ";
		}

		cout << list->item;
		list = list->next;
	}

    cout << "}" << endl;
}

/* sublistExtend(bis, list, prefix)
 * This function extends the list at the specified index, 'list,' in the AllBis
 * 'bis' to include the given 'prefix' as an element in the next BIS. */

void sublistExtend(AllBis* bis, int list, int prefix)
{
	setList(bis->lists[list+1], new ListCell(prefix, bis->lists[list]));

    if (list+1 > bis->listLongest)
    {
        bis->listLongest++;
    }

	if (PROG_TRACE)
	{
		cout << "      List at index [" << list+1 << "]: ";
		sublistPrint(bis->lists[list+1]);
	}
}

/* sublistExtensionIndex(bis, prefix, book)
 * This function scans through all of the sublists in the AllBis, 'bis,'
 * to locate which should be extended by 'prefix' into the next best increasing
 * sublist. The Book 'book' contains the heights of mountains to be used in the
 * location of the sublist to be extended. */

int sublistExtensionIndex(AllBis* bis, int prefix, Book book)
{
    if (PROG_TRACE)
    {
		cout << "PROG: Index-Finder for [" << book->mountains[prefix].elevation
			 << "]: ";
    }

	int cList;
	for(cList=bis->listLongest;
		cList!=0 && !mountainShorter(book, bis->lists[cList]->item, prefix);
		cList--)
	{
		if (PROG_TRACE)
		{
			cout << "F ";
		}
	}

    if (PROG_TRACE)
    {
		cout << "T" << endl << "      List index [" << cList
             << "] requires update." << endl;
    }

    return cList;
}

/* setList(cellA, cellB)
 * This function updates the reference counters for the ListCells cellA and
 * cellB. It then sets cellA to point to cellB. */

void setList(ListCell*& cellA, ListCell* cellB)
{
	cellReferenceBump(cellB);
	cellReferenceDrop(cellA);
	cellA = cellB;
}

/* cellReferenceBump(cell)
 * This function increments the ListCell "cell's" reference counter by 1. */

void cellReferenceBump(ListCell* cell)
{
	if (cell != NULL)
	{
		if (PROG_TRACE && PROG_TOGG_CELLREFERENCE)
		{
			cout << "PROG: Cell [" << cell << "] has new ref. Count ["
				 << cell->references << "]." << endl;
		}

		cell->references++;
	}
}

/* cellReferenceDrop(cell)
 * This function deducts from the reference count of the ListCell 'cell,'
 * destroying it if it has no more references. */

void cellReferenceDrop(ListCell* cell)
{
	if (cell != NULL)
	{
		cell->references--;

		if (PROG_TRACE && PROG_TOGG_CELLREFERENCE)
		{
			cout << "PROG: Cell [" << cell << "] lost a ref.  Count ["
				 << cell->references << "]." << endl;
		}
		
		if (cell->references <= 0)
		{
			if (PROG_TRACE)
			{
				cout << "PROG: Cell [" << cell << "] was deleted! Cell item ["
					 << cell->item << "]" << endl;
			}
			
			cellReferenceDrop(cell->next);

			if (PROG_TOGG_CELLDELETION)
			{
				delete cell;
			}
		}
	}
}

/* mountainPrintAll(bis, book)
 * This function prints the longest, best increasing sublist in the AllBis*
 * 'bis.' The Book 'book' is used as reference for mountain indices in the best
 * increasing sublist. */

void mountainPrintAll(AllBis* bis, Book book)
{
	cout << "These " << bis->listLongest << " mountain(s) should be climbed:"
		 << endl;
	mountainPrintSingle(bis->lists[bis->listLongest], book);
}

/* mountainPrintSingle(cell, book)
 * This function prints a single mountain's name and elevation from the Book
 * 'book,' using the item in ListCell 'cell' for the index of the mountain
 * to be printed. */

void mountainPrintSingle(ListCell* cell, Book book)
{
	if (cell != NULL)
	{
		mountainPrintSingle(cell->next, book);
		printf("    %5i, %s\n", book->mountains[cell->item].elevation,
			   book->mountains[cell->item].name);
	}
}
