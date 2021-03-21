#ifndef CLIENT_H
#define CLIENT_H
#include "declarations.h"

// class to represent a client
class Client {
public:
    // information about the client
    std::string name;
    int arrivalTime;
    int serviceTime;
    int seatNumber;

    // the seat number client receives (0 means they couldn't find a seat)
    int realSeatNumber;

    // thread ID of the client (ie: which thread clientFunc call belongs to)
    pthread_t thread;

    // condition variable and its mutex.
    // These are required to put client to sleep until teller wakes them up
    pthread_cond_t condVar;
    pthread_mutex_t condMutex;

    // creates empty client
    Client();
    
    // creates a client from {name, arrival t., service t., seat n.}
    Client(const std::vector<std::string> &vec); 
    
    ~Client();

    // waits for condVar to change
    void 
    goToSleep();
    
    // sleeps for arrivalTime ms
    void 
    waitForArrival();
    
    // changes condVar of teller
    void 
    wakeUpTeller(Teller &teller);
    
    // tries to lock a teller and set their pointer, returns true if successful
    bool 
    tryToAcquireTeller( Teller &teller);

    // releases mutex of the teller
    void
    releaseTeller(Teller &teller);
};
#endif