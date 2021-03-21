# ticket-office-project
Solution for an assignment of Operating Systems course. The objective is to simulate ticket office of a theater such that three tellers concurrently serve clients and reserve the seats for them. The project makes use of mutexes, semaphores, and condition variables of  the POSIX interface.

This solution is written with object-oriented programming paradigm and with readability in mind. The code is separated into classes and each class has two files (header and source). This can also help us reduce compilations times, only the changed classes need to be recompiled.


## Requirements

-  `g++`
-  A POSIX compliant operating system


## Building
```
git clone https://github.com/omarr09/ticket-office-project
cd https://github.com/omarr09/ticket-office-project
```
To compile:
```
make
```

To run:
```
make
./simulation.o <input> <output>
```
*Here \<input\> is path of the input file  \<output\> is path of the output file.*

To delete object files:
```
make clear
```
To delete object files and the executable:
```
make clearall
```


## Input format
First line of the input file has name of the theater. Second line has number of clients. Rest of the input file lists client, one client per line. For each client; their name, arrival time, service time, and requested seat number are specified (comma-separated). 