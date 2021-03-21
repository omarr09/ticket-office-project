#ifndef READER_H
#define READER_H
#include "declarations.h"

// class for reading input from a file
class Reader {
public:
    std::ifstream stream; // file stream which we get input from

    Reader(const std::string &path); // initializes stream from path
    
    // gets a line of string, trims CR (for Windows), and returns the string
    std::string
    getLine(); 

    // gets a line and extracts the integer from it
    int 
    getLineAsInt();    
    
    // gets a line and splits it at delims
    std::vector<std::string>
    getLineAsVector(char delim); 
};
#endif