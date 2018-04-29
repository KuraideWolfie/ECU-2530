// Inclusion statements
#include "equiv.h"
#include <cstdio>
using namespace std;

// Function prototypes
void printEqual(ER e, int n1, int n2);
void showInfo(ER e, int n);

int main()
{
    // Create a new equivalence relation
    ER R = newER(7);

    showInfo(R, 7);
    showER(R, 7);
    merge(R, 3, 5);
    showInfo(R, 7);
    showER(R, 7);
    merge(R, 5, 1);
    showInfo(R, 7);
    showER(R, 7);
    merge(R, 2, 1);
    showInfo(R, 7);
    showER(R, 7);
    merge(R, 6, 7);
    showInfo(R, 7);
    showER(R, 7);
    merge(R, 1, 6);
    showInfo(R, 7);
    showER(R, 7);

	// Show information again (leader change)
    showInfo(R, 7);

    // Destroy the equivalence relation
    destroyER(R);

    // Return exit code
    return 0;
}

/* printEqual(e, n1, n2)
 * Prints whether or not two integers are equivalent in the given equivalence
 * relation, e */
void printEqual(ER e, int n1, int n2)
{
    printf("Is %i equivalent to %i? ", n1, n2);
    equivalent(e, n1, n2) ? printf("Yes\n") : printf("No\n");
}

/* showInfo(e, n)
 * Prints the number of constituents and boss for all entries in e, which is
 * of size n. */
void showInfo(ER e, int n)
{
    // Print information about each entry in e (the index, the boss, and
    // constituents in the format index:boss:subs) with a linebreak
    printf("IND | LEA | SUB\n");
    for(int i=1; i<n+1; i++)
    {
        printf(" %i  |  %i  |  %i\n", i, e[i].boss, e[i].numConstituents);
    }
}