#ifndef TELLER_H
#define TELLER_H
#include "declarations.h"

// class to represent a teller
class Teller {
public:
    // mutex for client to check if teller is available, if so, client locks this
    pthread_mutex_t mutex; 

    // index of the teller (0 for A, 1 for B, 2 for C)
    int index; 

    // the client they are serving right now
    Client *currentClientPtr = nullptr; 

    // thread ID of the teller (ie: which thread tellerFunc call belongs to)
    pthread_t thread;

    // condition variable and its mutex.
    // These are required to put teller to sleep until client wakes them up
    pthread_cond_t condVar;
    pthread_mutex_t condMutex;

    Teller();          // creates empty teller

    Teller(int index); // creates teller with index

    ~Teller();

    void 
    goToSleep(); // waits for condVar to change

    void
    emplaceCurrentClient(); // finds a seat for current client, or fails trying

    void 
    printCurrentClientTicket(); // prints ticket details of current client

    void
    printGreetingMessage();     // prints "Teller X has arrived" message

    void
    waitForService();      // sleeps for service time of the current client

    void
    wakeUpCurrentClient(); // changes condVar of the current client
};
#endif