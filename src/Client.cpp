#include "Client.h"
#include "Teller.h"
using namespace std;

Client::Client() = default;

Client::Client(const vector<string> &vec):
    name(vec[0]),
    arrivalTime(stoi(vec[1])),
    serviceTime(stoi(vec[2])),
    seatNumber(stoi(vec[3])) {
    pthread_mutex_init(&condMutex, nullptr);
    pthread_cond_init(&condVar, nullptr);
    pthread_mutex_lock(&condMutex);
}

Client::~Client() {
    pthread_mutex_trylock(&condMutex);
    pthread_mutex_unlock(&condMutex);
    pthread_mutex_destroy(&condMutex);
    pthread_cond_destroy(&condVar);
}

void
Client::goToSleep() {
    pthread_cond_wait(&condVar, &condMutex); 
}

void
Client::waitForArrival() {
    usleep(arrivalTime * 1000);
}

void
Client::wakeUpTeller(Teller &teller) {
    pthread_cond_signal(&teller.condVar);
}

bool
Client::tryToAcquireTeller(Teller &teller) {
    int success = pthread_mutex_trylock(&teller.mutex);
    if (success == 0) {
        teller.currentClientPtr = this;
        return true;
    } else {
        return false;
    }
}

void
Client::releaseTeller(Teller &teller) {
    pthread_mutex_unlock(&teller.mutex);
}