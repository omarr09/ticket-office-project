#include "Client.h"
#include "ClientList.h"
#include "Printer.h"
#include "Reader.h"
#include "Seats.h"
#include "Teller.h"
#include "TicketOffice.h"
using namespace std;

unique_ptr<TicketOffice> ticketOffice;
unique_ptr<Seats> seats;
unique_ptr<Printer> printer;

// Function of the client thread.
// Does the arrival wait, then waits in the queue until ticket office becomes
// available (by waiting for the semaphore). Then finds the first available
// teller, wakes them up and goes to sleep until they wake the client up. Then
// leaves the ticket office (by releasing the semaphore)
void* 
clientFunc(void *data) {
    Client &client = * (Client *) data;
    client.waitForArrival();

    ticketOffice->withSemaphore([&]() {
        for (auto &teller : ticketOffice->tellers) {
            bool success = client.tryToAcquireTeller(teller);
            if (success) {
                client.wakeUpTeller(teller);
                client.goToSleep();
                client.releaseTeller(teller);
                break;
            }
        }
    });

    return nullptr;
}

// Function for the teller thread. Waits for a client and processes their
// request in a loop. When a client comes they set teller's data, wakes them up,
// then goes to sleep themselves. Then teller waits for seatsMutex (to access
// available seats set). Teller processes client's request inside seatsMutex,
// then releases it, then wakes up the client
void* 
tellerFunc(void *data) {
    // make thread asynchronously cancellable
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, nullptr); 

    Teller &teller = *(Teller *)data;
    usleep(teller.index * 15000);
    teller.printGreetingMessage();
    while (true) {
        teller.goToSleep();
        seats->withMutex([&]() { teller.emplaceCurrentClient(); });
        teller.waitForService();
        teller.printCurrentClientTicket();
        teller.wakeUpCurrentClient();
    }
}

int 
main(int argc, char *argv[]) {
    if (argc != 3) {
        throw invalid_argument("Two command line arguments required.");
    }

    // Read input
    Reader reader{string(argv[1])};
    printer = make_unique<Printer>(string(argv[2]));
    string firstLine = reader.getLine();
    int size = 
        firstLine == "OdaTiyatrosu" ? 60 : 
        firstLine == "UskudarStudyoSahne" ? 80 : 
        200;
    seats = make_unique<Seats>(size);
    ClientList clientList(reader.getLineAsInt());
    for (auto &client : clientList) {
        client = Client(reader.getLineAsVector(','));
    }

    // Run simulation
    printer->println("Welcome to the Sync-Ticket!");
    ticketOffice = make_unique<TicketOffice>();
    ticketOffice->createTellerThreads();
    usleep(60000);
    clientList.createClientThreads();
    clientList.joinClientThreads();
    printer->println("All clients received service.");
    ticketOffice->cancelTellerThreads();
}