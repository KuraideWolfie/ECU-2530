# ECU-2530

## Assignment 03
### Assignment Description
This assignment was primarily a buildup for future assignments, where an equivalence relation tool/structure was to be developed and tested. The following operations were written for the equivalence relation structure:
- newER: Constructs, and returns, an ER structure
- destroyER: Destroys a previously-created ER structure
- equivalent: Tests whether two parameters – ‘x’ and ‘y’ – are in the same equivalence class
- merge: Merges the two equivalence classes that contain ‘x’ and ‘y’
### Source Files
equiv.cpp, equiv.h, equivtest.cpp
### Compilation, Testing, and Known Issues
```
Windows:
Compile: g++ -Wall -Werror -o equiv.exe equiv.cpp equiv.h equivtest.cpp
Testing: equiv

Linux:
Compile: g++ -Wall -Werror -o equiv equiv.cpp equiv.h equivtest.cpp
Testing: ./equiv
```
Notes:
- This assignment was the first exposure to structures in the C++ language; as such, I initialized variables without using a constructor. I am well aware of this fact, but to preserve the integrity of the code, I leave it unchanged, as it doesn’t impact the assignment in such a manner it cannot run.
