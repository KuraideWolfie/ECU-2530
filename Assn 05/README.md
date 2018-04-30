# ECU-2530

## Assignment 05
### Assignment Description
This assignment was the first introduction to priority queues and their creation, with the following operations being specified for a priority queue:
- isEmpty: Returns whether the queue is empty or not
- insert: Inserts a value with a given priority into the queue
- remove: Removes a value from the queue with the given priority
- printPriorityQueue: Prints the priority queue (debug function)
### Source Files
testpq.cpp, pqueue.h, pqueue.cpp
### Compilation, Testing, and Known Issues
```
Windows:
Compile: g++ -Wall -Werror -o testpq.exe pqueue.h pqueue.cpp testpq.cpp
Testing: testpq.exe

Linux:
Compile: g++ -Wall -Werror -o testpq pqueue.h pqueue.cpp testpq.cpp
Testing: ./testpq
```
