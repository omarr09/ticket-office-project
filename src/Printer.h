#ifndef PRINTER_H
#define PRINTER_H
#include "Client.h"
#include "Teller.h"
#include "declarations.h"

// class for thread safe printing of lines or ticket messages
class Printer {
public:
    std::ofstream stream;  // file stream which we write outputs to
    pthread_mutex_t mutex; // mutex for thread safe printing

    // initializes stream from path
    Printer(const std::string &path);
    
    ~Printer();
    
    // prints details of a ticket ("X recevied Y, ...")
    void
    printTicket(const Teller &teller, const Client &client, int seat);
    
    // prints any line
    void
    println(const std::string &str); 
};
#endif