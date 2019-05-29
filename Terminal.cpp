//
// Created by Admin on 5/25/2019.
//

#include <cstring>
#include <fstream>
#include "Terminal.h"

//___public functions section
//initialize terminal with commandLine arguments when start the program
Terminal::Terminal(int argc, char **argv) {
    //TODO - validation for arguments (1=-f)?

    for (int i=2; i<argc; i++) {
//        cout << "i:" << i << " argc:" << argc << " " << argv[i] << endl;
        if (strcmp(argv[i],"-p") == 0) {
//            cout << "finish, got -p" << endl;
            outfile = argv[i+1];
        } else {
            //input file
            try {
                openFile(argv[i], true);
            } catch (TerminalException ex) {
                cout << ex.getMessage() << endl;
            }
        }
    }
}

int Terminal::start() {
    cout << "start listening for input" << endl;
    ofstream ofs(outfile);
    string line;
    while ((getline(cin,line)) && line != "exit") {
        try {
            vector<string> lineVect = splitString(line,",");
            if (hashCommand(lineVect[0]) == print) {
                if (lineVect.size() != 1) throw CommandException();
                hb.print(ofs);
                continue;
            }
            if (hashCommand(lineVect[0]) == open) {
                if (lineVect.size() != 2) throw CommandException();
                openFile(lineVect[1], false);
                ofs << "Update was successful." << endl;
                continue;
            }
            if (lineVect.size() == 3 && (hashCommand(lineVect[3])) == shortest) {
                cout << "shortest command" << endl;
                shortestRoute(lineVect[0],lineVect[1]);
                continue;
            }
            switch (hashCommand(lineVect[1])) {
                case inbound:
                    if (lineVect.size() != 2) throw CommandException();
                    printInbound(lineVect[0], ofs);
                    break;
                case outbound:
                    if (lineVect.size() != 2) throw CommandException();
                    printOutbound(lineVect[0], ofs);
                    break;
                case inventory:
                    if (lineVect.size() != 3) throw CommandException();
                    boxCount(lineVect[0],lineVect[2], ofs);
                    break;
                default:
                    throw CommandException();
            }
        } catch (TerminalException ex) {
            cout << ex.getMessage() << endl;
        }
    }
    return 0;
}

//___private functions section
Terminal::command_code Terminal::hashCommand(string const &str) {
    if (str == "open") return open;
    if (str == "print") return print;
    if (str == "inbound") return inbound;
    if (str == "outbound") return outbound;
    if (str == "inventory") return inventory;
    if (str == "shortest") return shortest;
}

vector<string> Terminal::splitString(string str, string delimiter) {
    vector<string> result;
    size_t pos = 0;
    string token;
    while ((pos = str.find(delimiter)) != std::string::npos) {
        token = str.substr(0,pos);
        result.push_back(token);
        str.erase(0, pos+delimiter.length());
    }
    result.push_back(str);
    return result;
}

void Terminal::shortestRoute(string from, string to) {
    if (!hb.storageExist(from)) throw StorageExistException(from);
    if (!hb.storageExist(to)) throw StorageExistException(to);
    hb.getShortestRoute(from,to);
}

void Terminal::boxCount(string storageName, string time, ostream& os) {
    if (!hb.storageExist(storageName)) throw StorageExistException(storageName);
    int boxCount = hb.getBoxCount(storageName,time);
    os << boxCount << endl;
}

void Terminal::printInbound(string storageName, ostream &os) {
    if (!hb.storageExist(storageName)) throw StorageExistException(storageName);
    map<shared_ptr<Storage>,Weight> inboundList = hb.getInboundList(storageName);
    if (inboundList.size() == 0) {
        os << storageName << ": no inbound nodes" << endl;
        return;
    }
    map<shared_ptr<Storage>,Weight>::iterator it;
    for (it = inboundList.begin(); it != inboundList.end(); it++) {
        os << it->first.get()->getName() << "," << it->second.getMinutes() << endl;
    }
}

void Terminal::printOutbound(string storageName, ostream& os) {
    if (!hb.storageExist(storageName)) throw StorageExistException(storageName);
    map<shared_ptr<Storage>,Weight> adjList = hb.getStorage(storageName).get()->getAdjList();
    if (adjList.size() == 0) {
        os << storageName << ": no outbound nodes" << endl;
        return;
    }
    map<shared_ptr<Storage>,Weight>::iterator it;
    for (it = adjList.begin(); it != adjList.end(); it++) {
        os << it->first->getName() << "," << it->second.getMinutes() << endl;
    }
}

void Terminal::openFile(string fileName, bool initialize) {
//    cout << "open file named: " << fileName << endl;
    std::string::size_type sz;

    ifstream ifs(fileName);
    if (ifs) {
        string delimiter = ",";
        string line;
        shared_ptr<Storage> lastStorage;
        string departure_time;
        int numLine = 1;
        while (getline(ifs,line)) {
            if (lastStorage == nullptr) {
                //starting storage
                //TODO - validation, must be 2 arguments in vector (storageName,date)
                vector<string> storageVect = splitString(line,delimiter);
                if (storageVect.size() != 2) initialize ? throw InitializeException(fileName,numLine) : throw FileException(numLine);
//                cout << "firstLine: " << line << " vectSize: " << storageVect.size() << endl;
                string storageName = storageVect[0];
                if (storageName.size() > 16) initialize ? throw InitializeException(fileName,numLine) : throw FileException(numLine);
                departure_time = storageVect[1];
                if (hb.storageExist(storageName)) {
                    lastStorage = hb.getStorage(storageName);
                } else {
                    lastStorage = shared_ptr<Storage>(new Storage(storageName,0));
                    hb.addStorage(lastStorage);
                }
            } else {
                //must be 4 arguments in vector (storageName, arrival_time, boxAmount, departure_time)
                vector<string> storageVect = splitString(line,delimiter);
//                        cout << line << " vectSize: " << storageVect.size() << endl;
                //TODO - validation (storageName,arrival_time,boxAmount,departure_time)
                try {
                    if (storageVect.size() != 4) initialize ? throw InitializeException(fileName,numLine) : throw FileException(numLine);

                    string name = storageVect[0];
                    if (name.size() > 16) initialize ? throw InitializeException(fileName,numLine) : throw FileException(numLine);

                    int boxAmount = stoi(storageVect[2],&sz);
                    string arrival_time = storageVect[1];

                    Weight weight(boxAmount,departure_time,arrival_time);
                    departure_time = storageVect[3]; //change last departure_time

                    if (hb.storageExist(name)) {
                        //add to the exist one
//                            cout << "storage exist"<<endl;
                        shared_ptr<Storage> storage = hb.getStorage(name);
                        lastStorage.get()->addNeighbor(storage,weight,departure_time,arrival_time);
                        lastStorage = storage;
                    } else {
                        //put new storage
//                            cout << "put new storage " << endl;
                        shared_ptr<Storage> storage(new Storage(name,boxAmount));

                        hb.addStorage(storage);
                        lastStorage.get()->addNeighbor(storage, weight,departure_time,arrival_time);
                        lastStorage = storage; //change last storage in this line
                    }
                } catch (exception ex) {
//                    cout << ex.what() << endl;
                    initialize ? throw InitializeException(fileName,numLine) : throw FileException(numLine);
                }
            }
            numLine++;
        }
    } else {
        if (!initialize) throw FileException();
    }
}