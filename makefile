ARGS = -Wall -Wextra -Wpedantic -std=c++17 -lpthread

simulation.o: main3.o Client.o Teller.o Seats.o TicketOffice.o Printer.o Reader.o ClientList.o
	g++ main3.o Client.o Teller.o Seats.o TicketOffice.o Printer.o Reader.o ClientList.o -o simulation.o $(ARGS)

main3.o: ./src/main3.cpp ./src/Client.h ./src/Teller.h ./src/Seats.h ./src/TicketOffice.h ./src/Printer.h ./src/Reader.h ./src/declarations.h
	g++./src/ main3.cpp -c -o main3.o $(ARGS)

Client.o: ./src/Client.cpp ./src/Client.h ./src/Teller.h ./src/declarations.h
	g++ ./src/Client.cpp -c -o Client.o $(ARGS)

Teller.o: ./src/Teller.cpp ./src/Teller.h ./src/Seats.h ./src/Client.h ./src/Printer.h ./src/declarations.h
	g++ ./src/Teller.cpp -c -o Teller.o $(ARGS)

Seats.o: ./src/Seats.cpp ./src/Seats.h ./src/declarations.h
	g++ ./src/Seats.cpp -c -o Seats.o $(ARGS)

TicketOffice.o: ./src/TicketOffice.cpp ./src/TicketOffice.h ./src/eclarations.h
	g++ ./src/TicketOffice.cpp -c -o TicketOffice.o $(ARGS)

Printer.o: ./src/Printer.cpp ./src/Printer.h ./src/declarations.h
	g++ ./src/Printer.cpp -c -o Printer.o $(ARGS)

Reader.o: ./src/Reader.cpp ./src/Reader.h ./src/declarations.h
	g++ ./src/Reader.cpp -c -o Reader.o $(ARGS)

ClientList.o: ./src/ClientList.cpp ./src/ClientList.h ./src/declarations.h
	g++ ./src/ClientList.cpp -c -o ClientList.o $(ARGS)

clear:
	rm -f main3.o Client.o Teller.o Seats.o TicketOffice.o Printer.o Reader.o ClientList.o

clearall:
	rm -f main3.o Client.o Teller.o Seats.o TicketOffice.o Printer.o Reader.o ClientList.o simulation.o