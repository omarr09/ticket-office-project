#include "Printer.h"
using namespace std;

Printer::Printer(const string &path) {
    stream.open(path);
    if (!stream.is_open()) {
        throw runtime_error("Couldn't open " + path + " for output.\n");
    }
    pthread_mutex_init(&mutex, nullptr);
}

Printer::~Printer() {
    pthread_mutex_destroy(&mutex);
}

void
Printer::printTicket(const Teller &teller, const Client &client, int seat) {
    pthread_mutex_lock(&mutex);

    stream << client.name << " requests seat " << client.seatNumber
           << ", reserves " << (seat == 0 ? "None" : string("seat ") + to_string(seat))
           << ". Signed by Teller "
           << (teller.index == 0 ? "A" : teller.index == 1 ? "B" : "C") << "."
           << endl;

    pthread_mutex_unlock(&mutex);
}

void
Printer::println(const string &str) {
    pthread_mutex_lock(&mutex);
    stream << str << endl;
    pthread_mutex_unlock(&mutex);
}