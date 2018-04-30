// CSCI 2530
// Assignment: 1
// Author:     Matthew Morgan
// File:       closest.cpp
// Tab stops:  4

/* This program accepts the entry of six real numbers that represent coordinate points
 * on a plane, where the input is formatted as "x1 y1 x2 y2 x3 y3." It then displays
 * which of the coordinate pairs are the closest to each other. */

// Inclusion statements
#include <cstdio>
#include <cmath>
using namespace std;

// Function prototypes
void showInput(double x1, double y1, double x2, double y2, double x3, double y3);
void showOutput(double x1, double y1, double x2, double y2, double d);
double distance(double x1, double y1, double x2, double y2);
void consider(double x1, double y1, double x2, double y2, double x3, double y3);

int main()
{
	double x1, y1, x2, y2, x3, y3;
	scanf("%lf%lf%lf%lf%lf%lf", &x1, &y1, &x2, &y2, &x3, &y3);
	showInput(x1, y1, x2, y2, x3, y3);
	consider(x1, y1, x2, y2, x3, y3);
	return 0;
}

/*
 * showInput(x1, y1, x2, y2, x3, y3)
 * This function prints three coordinate points to the screen, where the three
 * coordinates are (x1, y1), (x2, y2), and (x3, y3).
 */

void showInput(double x1, double y1, double x2, double y2, double x3, double y3)
{
	printf("The three points are:\n%10.3lf %10.3lf\n%10.3lf %10.3lf\n%10.3lf %10.3lf\n\n",
		x1, y1, x2, y2, x3, y3);
}

/*
 * distance(x1, y1, x2, y2)
 * This function calculates the distance between two coordinate points, where the
 * first point is (x1, y1) and the second point is (x2, y2).
 */

double distance(double x1, double y1, double x2, double y2)
{
	double xDiff=x2-x1, yDiff=y2-y1;
	return sqrt((xDiff*xDiff)+(yDiff*yDiff));
}

/*
 * showOutput(x1, y1, x2, y2, d)
 * This function shows that the two coordinates, (x1, y1) and (x2, y2), are the
 * closest with the distance, d, between them.
 */

void showOutput(double x1, double y1, double x2, double y2, double d)
{
	printf("The closest two points are:\n%10.3lf %10.3lf\n%10.3lf %10.3lf\n\n",
		x1, y1, x2, y2);
	printf("The distance between those points is: %10.3lf\n\n", d);
}

/*
 * consider(x1, y1, x2, y2, x3, y3)
 * This function considers which of the coordinates, consisting of (x1, y1), (x2, y2),
 * and (x3, y3), are the closest together, showing each of the closest pairs.
 */

void consider(double x1, double y1, double x2, double y2, double x3, double y3)
{
    double *dist = new double[3];
    dist[0] = distance(x1, y1, x2, y2);
    dist[1] = distance(x2, y2, x3, y3);
    dist[2] = distance(x1, y1, x3, y3);

    if (!(dist[0]>dist[1] || dist[0]>dist[2]))
    {
        showOutput(x1, y1, x2, y2, dist[0]);
    }

    if (!(dist[1]>dist[2] || dist[1]>dist[0]))
    {
        showOutput(x2, y2, x3, y3, dist[1]);
    }

    if (!(dist[2]>dist[0] || dist[2]>dist[1]))
    {
        showOutput(x1, y1, x3, y3, dist[2]);
    }
}