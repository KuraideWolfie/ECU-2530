// CSCI 2530
// Assignment: 6
// Author:     Matthew Morgan
// File:       dijkstra.cpp
// Tab stops:  4

/* This file contains structures and functions relevant to the creation of
 * graphs and the insertion of edges therein. Also contained are functions
 * in regards to sending and processing 'signals' to find the shortest
 * path between a starting vertex and ending vertex in a graph taken from
 * the standard input. */

// Inclusion statements
#include <cstdio>
#include <iostream>
#include <cstring>
#include "pqueue.h"
using namespace std;

// Global variables
bool PROG_TRACE = false; // Toggles trace-statement inclusion during runtime.

/* Edge represents a single edge in an adjacency list of edges in a graph.
 * vertexFrom is the vertex where the edge begins.
 * vertexTo is the vertex where the edge terminates.
 * weight is the weight of the edge.
 * nextEdge is a pointer to the next edge in the list. */

struct Edge
{
    int vertexFrom, vertexTo;
    double weight;
    Edge* nextEdge;
    Edge(int vF, int vT, double w, Edge* next)
    {
        vertexFrom = vF;
        vertexTo = vT;
        weight = w;
        nextEdge = next;
    }
};

/* Vertex represents a single vertex of a graph.
 * distShortest is the vertex's shortest distance from the start vertex.
 * signaled specifies whether a signal has reached the vertex.
 * incidenceList is the start of a linked list of edges incident to the
 * vertex. previous is the prior vertex in the path from the start vertex. */

struct Vertex
{
    Edge* incidenceList;
    double distShortest;
    bool signaled;
    int previous;
    Vertex()
    {
        incidenceList = NULL;
        distShortest = -1;
        signaled = false;
        previous = -1;
    }
};

/* Graph represents a full graph of vertices and edges.
 * vertices is an array of Vertex that contain information for each vertex.
 * edgeCount is the current number of edges in the graph. */

struct Graph
{
    int vertexCount, edgeCount;
    Vertex* vertices;
    Graph(int vCount)
    {
        vertexCount = vCount;
        vertices = new Vertex[vCount+1];
        edgeCount = 0;
    }
};

// Function prototypes
Graph readGraph(int pntArray[]);
void printGraph(Graph& g);
void printEdge(Edge*& edge, int cVertex);
void insertEdge(Graph& g, int vFrom, int vTo, double weight);
void signalSend(PriorityQueue& q, int vStart, int vEnd, double time);
void signalSendAll(Graph& g, PriorityQueue& q, int vertex);
void signalProcess(Graph& g, PriorityQueue& q, Event* e);
Event* signalFetch(PriorityQueue &q);
void pathFind(Graph& g, PriorityQueue& q, int endPoints[]);
void pathPrint(Graph& g, int endVertex);

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
        }
        else
        {
			cout << "usage: dijkstra [-t]" << endl;
            return false;
        }
    }
    return true;
}

int main(int argc, char** argv)
{
    if (!progArgumentCheck(argc, argv))
    {
        return 0;
    }

    int endPoints[] = {0, 0};
    PriorityQueue eventQueue = PriorityQueue();
    Graph graph = readGraph(endPoints);
    printGraph(graph);

    if (PROG_TRACE)
    {
        cout << "PROG: The start and end vertices are " << endPoints[0]
             << " and " << endPoints[1] << " respectively." << endl;
    }

    pathFind(graph, eventQueue, endPoints);
	printf("Shortest path between vertices %i and %i, of length %.3f is:\n",
		endPoints[0], endPoints[1], graph.vertices[endPoints[1]].distShortest);
    pathPrint(graph, endPoints[1]);
    cout << endl;
    return 0;
}

/* readGraph(pntArray)
 * This function creates a graph by reading in data from the standard input.
 * After reading has been completed, the Graph structure is returned.
 * Sample input is as follows:
 * |----------------------------------|
 * | 3       | Number of vertices     |
 * | 1 2 5.0 | Edge 1 data            |
 * | 2 3 0.0 | Edge 2 data            |
 * | 1 3 4.3 | Edge 3 data            |
 * | ...     | Further edge data      |
 * | 0       | End of edge data       |
 * | 1 3     | Start and end vertices |
 * |----------------------------------| */

Graph readGraph(int pntArray[])
{
    int vCount, eFrom, eTo;
    double eWeight;
    cin >> vCount >> eFrom;
    Graph g = Graph(vCount);

    if (PROG_TRACE)
    {
        cout << "PROG: Beginning edge insertion." << endl;
    }

    while(eFrom != 0)
    {
        cin >> eTo >> eWeight;
        insertEdge(g, eFrom, eTo, eWeight);
        if (PROG_TRACE)
        {
            cout << "     New edge inserted with vertices (" << eFrom << ","
                 << eTo << ") and weight " << eWeight << "." << endl;
        }
        cin >> eFrom;
    };

    cin >> pntArray[0] >> pntArray[1];
    return g;
}

/* printGraph(g)
 * This function prints the edges and number of vertices of the graph g.*/

void printGraph(Graph& g)
{
    cout << "The graph contains " << g.vertexCount << " vertices and "
         << g.edgeCount << " edges." << endl;
    cout << "The edges are as follows: " << endl;
    for (int i = 1; i < g.vertexCount + 1; i++)
    {
        printEdge(g.vertices[i].incidenceList, i + 1);
    }
}

/* printEdge(edge, cVertex)
 * This function prints the vertices and weight of a single edge. cVertex is
 * the vertex up to which all edges have currently been printed. */

void printEdge(Edge*& edge, int cVertex)
{
    if (edge != NULL) {
        if (edge->vertexTo >= cVertex)
        {
            cout << "  (" << edge->vertexFrom << "," << edge->vertexTo << ")"
                 << " weight " << edge->weight << endl;
        }
        printEdge(edge->nextEdge, cVertex);
    }
}

/* insertEdge(g, vFrom, vTo, weight)
 * This function inserts an edge into the graph, g. The edge is listed for both
 * the vertex where it begins, vFrom, and the vertex it terminates, vTo, with
 * a weight of 'weight'. */

void insertEdge(Graph& g, int vFrom, int vTo, double weight)
{
    g.vertices[vFrom].incidenceList = new Edge(vFrom, vTo, weight,
		g.vertices[vFrom].incidenceList);
    g.vertices[vTo].incidenceList = new Edge(vTo, vFrom, weight,
		g.vertices[vTo].incidenceList);
    g.edgeCount++;
}

/* signalSend(q, vStart, vEnd, time)
 * This function sends a signal from vertex vStart to vertex vEnd, transpiring
 * in 'time' seconds. The signal is stored as an event in the event queue, q.*/

void signalSend(PriorityQueue& q, int vStart, int vEnd, double time)
{
    Event* e = new Event(vStart, vEnd, time);
    insert(q, e, time);

    if (PROG_TRACE)
    {
        cout << "        Signal sent to [" << vEnd << "] with time " << time
             << "." << endl;
    }
}

/* signalSendAll(g, q, vertex)
 * This function sends a signal to all vertices adjacent to vertex in the
 * specified graph, g. Signals are stored via events in the event queue, q. */

void signalSendAll(Graph& g, PriorityQueue& q, int vertex)
{
    if (PROG_TRACE)
    {
        cout << "      Sending signals to adjacent vertices." << endl;
    }

    Vertex cVertex = g.vertices[vertex];
    for(Edge* cEdge = cVertex.incidenceList; cEdge != NULL;
        cEdge = cEdge->nextEdge)
    {
        if (!g.vertices[cEdge->vertexTo].signaled)
        {
            signalSend(q, vertex, cEdge->vertexTo,
                       cVertex.distShortest + cEdge->weight);
        }
        else if (PROG_TRACE)
        {
            cout << "        Vertex [" << cEdge->vertexTo << "] already "
                 << "signalled... Signal not sent." << endl;
        }
    }
}

/* signalProcess(g, q, e)
 * This function processes a single event, e, that is stored within the event
 * queue, q. The recipient vertex, in graph g, will be signalled if it hasn't
 * already; elsewise, the event is ignored entirely. */

void signalProcess(Graph& g, PriorityQueue& q, Event* e)
{
    Vertex* recipient = &g.vertices[e->receiver];
    if (PROG_TRACE)
    {
        cout << "PROG: Vertex [" << e->receiver << "] received a signal."
             << " Sender: " << e->sender << ", Time: " << e->time << endl;
    }
    if (!recipient->signaled)
    {
        recipient->signaled = true;
        recipient->previous = e->sender;
        recipient->distShortest = e->time;
        if (PROG_TRACE)
        {
            cout << "      Vertex [" << e->receiver << "] updated. Previous: "
                 << e->sender << ", Time from start: " << e->time << endl;
        }
        signalSendAll(g, q, e->receiver);
    }

    delete e;
}

/* signalFetch(q)
 * This function fetches a signal from the specified event queue, q, and
 * returns the signal. */

Event* signalFetch(PriorityQueue &q)
{
    PQItemType signal;
    PQPriorityType time;
    remove(q, signal, time);

    if (PROG_TRACE)
    {
        cout << "PROG: Event removed from the event queue! Event parameters "
             << "[sender, receiver, time] -> [" << signal->sender << ","
             << signal->receiver << "," << time << "]" << endl;
    }

    return signal;
}

/* pathFind(g, q, endPoints)
 * This function finds the shortest path from the start and end vertices
 * contained in an array, pathPoints, in the graph g utilizing a priority
 * queue, q, to store generated signals. */

void pathFind(Graph& g, PriorityQueue& q, int endPoints[])
{
    signalSend(q, 0, endPoints[0], 0);
    while (!g.vertices[endPoints[1]].signaled)
    {
        signalProcess(g, q, signalFetch(q));
    }
}

/* pathPrint(g, endVertex)
 * This function prints out a path between two vertices in graph g, ending with
 * the vertex endVertex and beginning with another, arbitrary vertex. */

void pathPrint(Graph& g, int endVertex)
{
    Vertex me = g.vertices[endVertex];
    if (me.previous == 0)
    {
        cout << endVertex;
    }
    else
    {
        pathPrint(g, me.previous);
        cout << " -> " << endVertex;
    }
}
