#include "Teller.h"
#include "Client.h"
#include "Printer.h"
#include "Seats.h"
using namespace std;
extern unique_ptr<Seats> seats;
extern unique_ptr<Printer> printer;

Teller::Teller() = default;

Teller::Teller(int index) : index(index) {
    pthread_mutex_init(&mutex, nullptr);
    pthread_mutex_init(&condMutex, nullptr);
    pthread_cond_init(&condVar, nullptr);
    pthread_mutex_lock(&condMutex);
}

Teller::~Teller() {
    pthread_mutex_trylock(&condMutex);
    pthread_mutex_unlock(&condMutex);
    pthread_mutex_destroy(&condMutex);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&condVar);
}

void
Teller::goToSleep() { 
    pthread_cond_wait(&condVar, &condMutex); 
}

void 
Teller::emplaceCurrentClient() {
    Client &client = *currentClientPtr;
    if (set<int>::iterator itr;
        (itr = seats->available.find(client.seatNumber)) !=
        seats->available.end()) {
        currentClientPtr->realSeatNumber = client.seatNumber;
        seats->available.erase(itr);
    } else if (!seats->available.empty()) {
        currentClientPtr->realSeatNumber = *seats->available.begin();
        seats->available.erase(seats->available.begin());
    } else {
        currentClientPtr->realSeatNumber = 0;
    }
}

void 
Teller::printCurrentClientTicket() {
    printer->printTicket(*this, *currentClientPtr,
                         currentClientPtr->realSeatNumber);
}

void 
Teller::printGreetingMessage() {
    printer->println(string("Teller ") +
                     (index == 0 ? "A" : index == 1 ? "B" : "C") +
                     " has arrived.");
}

void 
Teller::waitForService() {
    Client &client = *currentClientPtr;
    usleep(client.serviceTime * 1000);
}

void 
Teller::wakeUpCurrentClient() {
    Client &client = *currentClientPtr;
    pthread_cond_signal(&client.condVar);
}
