#include "ClientList.h"
#include "Client.h"
using namespace std;

ClientList::ClientList(int size) { 
    clients = vector<Client>(size); 
}

std::vector<Client>::iterator
ClientList::begin() {
    return clients.begin();
}

std::vector<Client>::iterator
ClientList::end() {
    return clients.end();
}

void
ClientList::createClientThreads() {
    for (auto &client : clients) {
        pthread_create(&client.thread, nullptr, clientFunc, (void *) &client);
    }
}

void 
ClientList::joinClientThreads() {
    for (auto &client : clients) {
        pthread_join(client.thread, nullptr);
    };
}