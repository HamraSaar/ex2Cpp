//
// Created by Admin on 5/25/2019.
//

#include <algorithm>
#include "HoogieBoogie.h"

void HoogieBoogie::addStorage(shared_ptr<Storage> newStorage) {
    storageList.push_back(newStorage);
}

bool HoogieBoogie::storageExist(const string name) {
    vector<shared_ptr<Storage>>::iterator it = find_if(storageList.begin(),storageList.end(), [name](shared_ptr<Storage> storage) {
        return storage.get()->getName() == name;
    });
    return it != storageList.end();
}

shared_ptr<Storage> HoogieBoogie::getStorage(string name) {
    if (!storageExist(name)) { return nullptr; }
    vector<shared_ptr<Storage>>::iterator it = find_if(storageList.begin(),storageList.end(), [name](shared_ptr<Storage> storage) {
        return storage.get()->getName() == name;
    });
    return *it;
}

map<shared_ptr<Storage>,Weight> HoogieBoogie::getInboundList(string name) {
    map<shared_ptr<Storage>,Weight> result;
    if (!storageExist(name)) return result;
    vector<shared_ptr<Storage>>::iterator it;
    for (it = storageList.begin(); it != storageList.end(); it++) {
        if (it->get()->getName() == name) continue;
        map<shared_ptr<Storage>,Weight> adjList = it->get()->getAdjList();
        map<shared_ptr<Storage>,Weight>::iterator it2;
        for (it2 = adjList.begin(); it2 != adjList.end(); it2++) {
            if (it2->first->getName() == name) {
                result[*it] = it2->second;
                break;
            }
        }
    }
    return result;
}

void HoogieBoogie::print(ostream &os) {
    vector<shared_ptr<Storage>>::iterator it;
    for (it = storageList.begin(); it != storageList.end(); it++) {
        string from = it->get()->getName();
        map<shared_ptr<Storage>,Weight> adjList = it->get()->getAdjList();
        map<shared_ptr<Storage>,Weight>::iterator it2;
        for (it2 = adjList.begin(); it2 != adjList.end(); it2++) {
            os << "from: " << from << ", to: " << it2->first->getName() << ", minutes: " << it2->second.getMinutes() << ", cases: " << it2->second.getBoxAmount() << endl;
        }
    }
}

int HoogieBoogie::getBoxCount(string storageName, string time) {
    int boxCount = 0;
    //get arrived boxes before the wanted time and add to boxCount
    map<shared_ptr<Storage>,Weight> inboundList = getInboundList(storageName);
    map<shared_ptr<Storage>,Weight>::iterator inboundIt;
    for (inboundIt = inboundList.begin(); inboundIt != inboundList.end(); inboundIt++) {
        boxCount += inboundIt->second.getArrivalBoxCount(time);
    }
    //get departure boxes before the wanted time and sub from boxCount
    map<shared_ptr<Storage>,Weight> outboundList = getStorage(storageName)->getAdjList();
    map<shared_ptr<Storage>,Weight>::iterator outboundIt;
    for (outboundIt = outboundList.begin(); outboundIt != outboundList.end(); outboundIt++) {
        boxCount -= outboundIt->second.getDepartureBoxCount(time);
    }
    return boxCount;
}

void HoogieBoogie::getShortestRoute(string from, string to) {

}

void HoogieBoogie::diajkstra(string srcName) {
     
    vector<shared_ptr<Storage>>::iterator svIt; //storage vector iterator
    map<string,bool>::iterator sptIt;
    map<string,int> dist;
    map<string,bool> sptSet;
    map<string,vector<string>> route;

    for (svIt = storageList.begin(); svIt != storageList.end(); svIt++) {
        //initialize all distances as INFINITE and sptSet as false
        string name = svIt->get()->getName();

        dist[name] = INTMAX_MAX;
        sptSet[name] = false;
    }

    dist[srcName] = 0;

    for (sptIt = sptSet.begin(); sptIt != sptSet.end(); sptIt++) {

        string u = minDistance(dist,sptSet);
        sptSet[u] = true;

        shared_ptr<Storage> storage = getStorage(u);
        map<string,bool>::iterator sptIt2;
        for (sptIt2 = sptSet.begin(); sptIt2 != sptSet.end(); sptIt2++) {

        }
    }

}
string minDistance(map<string,int> dist, map<string,bool> sptSet) {
    int min = INTMAX_MAX;
    string minName;
    map<string,bool>::iterator it;
    for (it = sptSet.begin(); it != sptSet.end(); it++) {
        if (it->second == false && dist[it->first] <= min) {
            min = dist[it->first];
            minName = it->first;
        }
    }
    return minName;
}