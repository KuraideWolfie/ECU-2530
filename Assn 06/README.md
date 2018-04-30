# ECU-2530

## Assignment 06
### Assignment Description
This assignment utilizes the priority queue tool from assignment 5 for executing Dijkstra’s algorithm. It takes a graph of vertices and edges, finding the shortest path from vertex A to B, which are specified by the user. This is done by sending a series of signals from the starting vertex, visiting each of the surrounding ones in the order of lowest weight, until the last vertex is reached.
### Source Files
dijkstra.cpp, event.h, pqueue.h, pqueue.cpp
### Compilation, Testing, and Known Issues
```
Windows:
Compile: g++ -Wall -Werror -o dijkstra.exe dijkstra.cpp event.h pqueue.h pqueue.cpp
Testing: dijkstra <./data/graph.txt -t

Linux:
Compile: g++ -Wall -Werror -o dijkstra dijkstra.cpp event.h pqueue.h pqueue.cpp
Testing: ./dijkstra <./data/graph.txt -t
```
Notes:
- 2 test files are provided for the program in ‘data.’
- Tracing is available for this program. You can do this by toggling `PROG_TRACE` to true in the file dijkstra.cpp, or executing the program with the `-t` toggle as shown above.
- The input for the assignment is as follows:<br/>[number of vertices]<br/>[edge start] [edge end] [edge weight]<br/>[edge start] [edge end] [edge weight]<br/>...<br/>0<br/>[start vertex] [end vertex]
- The input of this program should include a possible shortest path for the start and end vertices. All edges should, in addition, have positive weights.
