#include "Seats.h"
using namespace std;

Seats::Seats(int size) {
    pthread_mutex_init(&mutex, nullptr);
    for (int i = 1; i <= size; i++) {
        available.insert(available.end(), i);
    }
}

Seats::~Seats() { pthread_mutex_destroy(&mutex); }

void 
Seats::withMutex(function<void()> func) {
    pthread_mutex_lock(&mutex);
    func();
    pthread_mutex_unlock(&mutex);
}