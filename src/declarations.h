#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <set>
#include <tuple>
#include <vector>

#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

class Client;
class Teller;
class Seats;
class TicketOffice;
class Printer;
class Reader;
class ClientList;

void* clientFunc(void *);
void* tellerFunc(void *);

#endif