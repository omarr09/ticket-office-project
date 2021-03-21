#ifndef CLIENTLIST_H
#define CLIENTLIST_H
#include "declarations.h"

// class to represent all clients
class ClientList {
public:
    std::vector<Client> clients; // client data

    // initializes clients vector with size
    ClientList(int size); 

    // returns an iterator to the beginning of clients
    std::vector<Client>::iterator
    begin(); 

    // returns an iterator to the end of clients
    std::vector<Client>::iterator
    end();                      

    // executes clientFunc for all clients, in new threads
    void 
    createClientThreads(); 
    
    // joins these threads
    void 
    joinClientThreads(); 
};
#endif