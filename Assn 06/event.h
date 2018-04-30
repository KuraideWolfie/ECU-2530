// CSCI 2530
// Assignment: 6
// Author:     Matthew Morgan
// File:       event.h
// Tab stops:  4

#ifndef EVENT_H
#define EVENT_H

/* Event represents a single event (a signal being sent).
 * sender is the vertex sending the signal.
 * receiver is the vertex receiving the signal.
 * time is the moment the event transpires. */

struct Event
{
    int sender, receiver;
    double time;
    Event(int s, int r, double t)
    {
        sender = s;
        receiver = r;
        time = t;
    }
};

#endif
