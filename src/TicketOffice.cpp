#include "TicketOffice.h"
using namespace std;

TicketOffice::TicketOffice() : tellers{} {
    sem_init(&semaphore, 0, 3);
    for (int i = 0; i < 3; i++) {
        tellers[i].index = i;
    }
}

TicketOffice::~TicketOffice() { 
    sem_destroy(&semaphore); 
}

void 
TicketOffice::withSemaphore(function<void()> func) {
    sem_wait(&semaphore);
    func();
    sem_post(&semaphore);
}

void 
TicketOffice::createTellerThreads() {
    for (auto &teller : tellers) {
        pthread_create(&teller.thread, nullptr, tellerFunc, (void *)&teller);
    }
}

void 
TicketOffice::cancelTellerThreads() {
    for (auto &teller : tellers) {
        pthread_cancel(teller.thread);
    }
}