//
// Created by Admin on 5/26/2019.
//

#ifndef TRANSFERHB_TERMINALEXCEPTION_H
#define TRANSFERHB_TERMINALEXCEPTION_H

#include <exception>
#include <string>

using namespace std;

class TerminalException: public exception {
private:
    string msg;
public:
    TerminalException() = default;
    TerminalException(string msg) : msg(msg) {}
    string getMessage() {return msg;}
};

class InitializeException: public TerminalException {
public:
    InitializeException() = default;
    InitializeException(string fileName, int numLine) : TerminalException("Invalid input in file " + fileName + " at line " + to_string(numLine) + ".") {};
};

class FileException: public TerminalException {
public:
    FileException() : TerminalException("Error opening/reading the specified file.") {}
    FileException(int numLine) : TerminalException("Invalid input at line " + to_string(numLine) + ".") {};
};

class CommandException: public TerminalException {
public:
    CommandException() : TerminalException(
            "USAGE: 'open',<file> *or*\n"
            "       <node>,'outbound'/'inbound' *or*\n"
            "       <node>,'inventory',dd/mm HH:mm *or*\n"
            "       <node>,<node>,'shortest *or*\n"
            "       'exit' *to terminate*\n"
            ) {}
};

class StorageExistException: public TerminalException {
public:
    StorageExistException(string name) : TerminalException(name + " does not exist in the database") {}
};

#endif //TRANSFERHB_TERMINALEXCEPTION_H
