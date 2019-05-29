//
// Created by Admin on 5/25/2019.
//

#ifndef TRANSFERHB_HOOGIEBOOGIE_H
#define TRANSFERHB_HOOGIEBOOGIE_H

#include <iostream>
#include <vector>
#include <memory>
#include "Storage.h"

using namespace std;

class HoogieBoogie {
private:
    vector<shared_ptr<Storage>> storageList;
    void diajkstra(string);
    string minDistance(map<string,int> dist, map<string,bool> sptSet);
public:
    HoogieBoogie() = default;

    void addStorage(shared_ptr<Storage>);

    bool storageExist(string);

    shared_ptr<Storage> getStorage(string);

    map<shared_ptr<Storage>,Weight> getInboundList(string);

    void print(ostream &os);

    int getBoxCount(string, string);

    void getShortestRoute(string, string);

};


#endif //TRANSFERHB_HOOGIEBOOGIE_H
