//
// Created by Admin on 5/25/2019.
//

#ifndef TRANSFERHB_TERMINAL_H
#define TRANSFERHB_TERMINAL_H


#include "HoogieBoogie.h"
#include "TerminalException.h"

class Terminal {
private:
    HoogieBoogie hb;
    string outfile = "output.dat";
    static vector<string> splitString(string str, string delimiter);
    enum command_code {
        open,
        print,
        outbound,
        inbound,
        inventory,
        shortest
    };
    static command_code hashCommand(string const&);
    //terminal operations
    void openFile(string fileName, bool initialize);
    void printOutbound(string storageName, ostream& os);
    void printInbound(string storageName, ostream& os);
    void boxCount(string storageName, string time, ostream& os);
    void shortestRoute(string from, string to);
public:
    //initializer with arguments
    Terminal(int argc, char* argv[]);

    ~Terminal() = default;

    int start();
};


#endif //TRANSFERHB_TERMINAL_H
