// CSCI 2530
// Assignment: 4
// Author:     Matthew Morgan
// File:       mst.cpp
// Tab stops:  4

/*
 * This program takes input that represents the number of vertices and edges of a connected
 * graph. It then generates a minimal spanning tree from the edges of the graph.
 */

// Inclusion statements
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "equiv.h"
using namespace std;

// Constants
typedef int (*QSORT_COMPARE_TYPE)(const void*, const void*);
const int MAX_EDGES = 100;

/*
 * Edge represents a single edge of a connected graph.
 * vFrom is the vertex where the edge begins.
 * vTo is the vertex where the edge ends.
 * weight is the weight of the edge from vFrom to vTo.
 */
struct Edge
{
    int vFrom, vTo, weight;
    Edge()
    {
        vFrom = 0;
        vTo = 0;
        weight = 0;
    }
};

/*
 * Graph represents a weighted graph.
 * numVertices is the number of vertices in the graph.
 * edgeCur is the current number of edges in the graph.
 * edgeTtl is the total number of edges possible in the graph.
 */
struct Graph
{
    int numVertices, edgesCur, edgesTtl;
    Edge* myEdges;
    Graph(int nv)
    {
        edgesCur = 0;
        edgesTtl = MAX_EDGES;
        numVertices = nv;
        myEdges = new Edge[edgesTtl];
    }
};

// Function prototypes
void insertEdge(int u, int v, int w, Graph& g);
Graph readGraph();
void writeGraph(Graph& g);
void sortEdges(Graph& g);
Graph minimalSpanningTree(Graph& g);
int graphWeight(Graph& g);
int compareEdges(const Edge* A, const Edge* B);

int main()
{
    Graph graphFull = readGraph();
    cout << "Input Graph" << endl;
    writeGraph(graphFull);
    cout << endl;

    Graph graphMST = minimalSpanningTree(graphFull);
    cout << "Minimal Spanning Tree" << endl;
    writeGraph(graphMST);
    cout << endl;

    cout << "Weight of the spanning tree: " << graphWeight(graphMST) << endl;

    return 0;
}

/*
 * insertEdge(u, v, w, g)
 * This function inserts an edge between vertices u and v of weight w in the
 * graph g. If there isn't enough room, insertEdge does nothing.
 */
void insertEdge(int u, int v, int w, Graph& g)
{
    if (g.edgesCur < g.edgesTtl)
    {
        // Insert the smaller value as the starting vertex of the edge
        if (u > v)
        {
            g.myEdges[g.edgesCur].vFrom = v;
            g.myEdges[g.edgesCur].vTo = u;
        }
        else
        {
            g.myEdges[g.edgesCur].vFrom = u;
            g.myEdges[g.edgesCur].vTo = v;
        }

        g.myEdges[g.edgesCur].weight = w;
        g.edgesCur++;
    }
}

/*
 * readGraph()
 * This function reads in the number of vertices as well as all edge data
 * until a 0 is reached. Suitable input is as follows:
 * DATA    | WHAT IT REPRESENTS
 * ----------------------------
 * 4       | Number of vertices
 * 1 2 10  | Edge 1
 * 2 3 4   | Edge 2
 * 1 4 15  | Edge 3
 * 0       | End of edge data
 * ----------------------------
 */
Graph readGraph()
{
    int vCount, eStart, eEnd, eWeight;
    cin >> vCount;
    Graph g = Graph(vCount);

    do
    {
        cin >> eStart;
        if (eStart != 0)
        {
            cin >> eEnd;
            cin >> eWeight;
            insertEdge(eStart, eEnd, eWeight, g);
        }
    }
    while(eStart != 0);

    return g;
}

/*
 * writeGraph(g)
 * This function prints the vertices and weight of every edge in the graph g.
 */
void writeGraph(Graph& g)
{
    cout << "The graph has " << g.numVertices << " vertices and " << g.edgesCur
         << " edges." << endl;
    for(int i = 0; i < g.edgesCur; i++)
    {
        cout << "    Edge " << (i+1) << " | Vertices [" << g.myEdges[i].vFrom
             << ", " << g.myEdges[i].vTo << "], Weight " << g.myEdges[i].weight
             << endl;
    }
}

/*
 * sortEdges(g)
 * This function sorts the edges present in the graph g by weight in ascending
 * order.
 */
void sortEdges(Graph& g)
{
    qsort((void*) g.myEdges, g.edgesCur, sizeof(Edge), (QSORT_COMPARE_TYPE) compareEdges);
}

/*
 * compareEdges(A, B)
 * This function returns the difference of edge B's weight from edge A's weight.
 */
int compareEdges(const Edge* A, const Edge* B)
{
    return A->weight - B->weight;
}

/*
 * minimalSpanningTree(g)
 * This function creates a minimal spanning tree (as a graph) from the edges of
 * the graph g and returns the memory location of the new graph.
 */
Graph minimalSpanningTree(Graph& g)
{
    Graph mst = Graph(g.numVertices);
    //ER mstER = newER(g.edgesCur-1);
    ER mstER = newER(g.numVertices);
    sortEdges(g);

    for(int i = 0; i < g.edgesCur; i++)
    {
        if (!equivalent(mstER, g.myEdges[i].vFrom, g.myEdges[i].vTo))
        {
            insertEdge(g.myEdges[i].vFrom, g.myEdges[i].vTo, g.myEdges[i].weight, mst);
            merge(mstER, g.myEdges[i].vFrom, g.myEdges[i].vTo);
        }
    }

    destroyER(mstER);
    return mst;
}

/*
 * graphWeight(g)
 * This function returns the summized weight of all the edges in graph g.
 */
int graphWeight(Graph& g)
{
    int weightTtl = 0;
    for(int i = 0; i < g.edgesCur; i++)
    {
        weightTtl += g.myEdges[i].weight;
    }
    return weightTtl;
}
