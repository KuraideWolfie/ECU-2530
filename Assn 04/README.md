# ECU-2530

## Assignment 04
### Assignment Description
This assignment was to perform the minimal spanning tree algorithm, creating a minimal spanning tree from a graph that’s provided via the standard input. The information about the initial, and resulting graphs, was to be printed to the screen. (This assignment also provided some information about redirecting input from text files and redirecting output to text files.)
### Source Files
equiv.h, equiv.cpp, mst.cpp
### Compilation, Testing, and Known Issues
```
Windows:
Compile: g++ -Wall -Werror -o mst.exe equiv.cpp equiv.h mst.cpp
Testing: mst.exe <./data/graph.txt

Linux:
Compile: g++ -Wall -Werror -o mst equiv.cpp equiv.h mst.cpp
Testing: ./mst <./data/graph.txt
```
Notes:
- 4 test input files are provided: graph.txt, graph2.txt, graph3.txt, graph4.txt
- The input for the assignment is as follows:<br/>[number of vertices]<br/>[edge start] [edge end] [edge weight]<br/>...<br/>0
