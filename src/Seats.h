#ifndef SEATS_H
#define SEATS_H
#include "declarations.h"

// class to represent available seats
class Seats {
public:
    std::set<int> available; // set of all available seats
    pthread_mutex_t mutex;   // mutex for accessing that set

    Seats(int size); // initializes available seats with numbers from 1 to size

    ~Seats();

    // locks mutex, applies func, releases mutex
    void
    withMutex(std::function<void()> func); 
};
#endif