#ifndef TICKETOFFICE_H
#define TICKETOFFICE_H
#include "Teller.h"
#include "declarations.h"

// class to represent the ticket office
class TicketOffice {
public:
    std::array<Teller, 3> tellers; // array of the three tellers
    sem_t semaphore; // semaphore for accessing the ticket office (size: 3)

    // initializes tellers' indexes
    TicketOffice(); 

    ~TicketOffice();
    
    // acquires sem., applies func, releases sem.
    void 
    withSemaphore(std::function<void()> func); 
    
    // executes tellerFunc for all tellers, in new threads
    void 
    createTellerThreads();   

    // cancels these threads
    void 
    cancelTellerThreads(); 
};
#endif