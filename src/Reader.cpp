#include "Reader.h"
using namespace std;

Reader::Reader(const string &path) {
    stream.open(path);
    if (!stream.is_open()) {
        throw runtime_error("Couldn't open " + path + " for input.\n");
    }
}

string
Reader::getLine() {
    string line;
    getline(stream, line);
    if (line.back() == '\r')
        line.pop_back();
    return line;
}

int 
Reader::getLineAsInt() { 
    return stoi(getLine());
}

vector<string> 
Reader::getLineAsVector(char delim) {
    string str = getLine();
    vector<string> strings;
    string currentStr;

    for (const char ch : str) {
        if (ch == delim) {
            if (!currentStr.empty()) {
                strings.push_back(currentStr);
                currentStr = "";
            }
        } else {
            currentStr += ch;
        }
    }

    if (!currentStr.empty()) {
        strings.push_back(currentStr);
    }

    return strings;
}