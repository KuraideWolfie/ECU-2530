# ECU-2530

## Assignment 07
### Assignment Description
This assignment’s goal was to generate a best increasing sublist (BIS) given a book of mountain names and elevations. Information about what a best increasing sublist is was provided, as well as light information about what structures to create to make the task easier. (A list of cells was utilized, and heavy emphasis was given to destroy cells when they have no further references.)
### Source Files
lis.cpp
### Compilation, Testing, and Known Issues
```
Windows:
Compile: g++ -Wall -Werror -o lis.exe lis.cpp
Testing: lis <./data/mixed.txt -t

Linux:
Compile: g++ -Wall -Werror -o lis lis.cpp
Testing: ./lis <./data/mixed.txt -t
```
Issues:
- There was, originally, an error in lis.cpp, in the Mountain structure, where I made the type of the variable `name` `char*`, and not `const char*`. The code would run in most scenarios, but with the ‘Werror’ compilation flag, it prevents execution; therefore, I fixed it prior to submission.
- This is more of a typographic dilemma, but I reference the ‘height’ of a Mountain as it’s elevation in-code.

Notes:
- This assignment is not coded to properly accept user input during runtime; a file MUST be provided, such as listed above, for testing, where the format of the file must have a mountain name, and then height beside it, per line. For example:<br/>-Example-<br/>Eiger 3970<br/>Everest 8848<br/>Denali 5500
- There are various, miniature trace/debugging toggles in the program. They are:<br/>PROG_TRACE: Enables trace statements<br/>PROG_TOGGLE_CELLDELETION: Toggles whether cells are deleted when they no longer have references to them<br/>PROG_TOGG_CELLREFERENCE: Prints an updated reference count for cells as they change<br/><br/>These toggles can also be manipulated by executing the program with the tag `-t` as shown above.
