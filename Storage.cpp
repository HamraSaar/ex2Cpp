//
// Created by Admin on 5/24/2019.
//

#include "Storage.h"

Storage::~Storage() {

}

const string &Storage::getName() const {
    return name;
}

ostream &operator<<(ostream &os, const Storage &storage) {
    os << "name: " << storage.name << " boxAmount: " << storage.boxAmount << " adjList: ";
    return os;
}

void Storage::setName(const string &name) {
    Storage::name = name;
}

int Storage::getBoxAmount() const {
    return boxAmount;
}

void Storage::setBoxAmount(int boxAmount) {
    Storage::boxAmount = boxAmount;
}

Storage::Storage(const string &name, int boxAmount) : name(name), boxAmount(boxAmount) {}

const map<shared_ptr<Storage>, Weight> &Storage::getAdjList() const {
    return adjList;
}

void Storage::setAdjList(const map<shared_ptr<Storage>, Weight> &adjList) {
    Storage::adjList = adjList;
}

Storage& Storage::operator=(Storage &rhs) {
    if (this != &rhs) {
        name = rhs.name;
        boxAmount = rhs.boxAmount;
        adjList = rhs.adjList;
    }
    return *this;
}

bool Storage::operator==(const Storage &rhs) const {
    return name == rhs.name;
}

bool Storage::operator!=(const Storage &rhs) const {
    return !(rhs == *this);
}

void Storage::addNeighbor(shared_ptr<Storage> neighbor, Weight weight, string departure_time, string arrival_time) {
    if (!adjList.insert(make_pair(neighbor,weight)).second) {
        //already a neighbor
        adjList[neighbor].addTruck(weight.getMinutes(),weight.getBoxAmount(),departure_time,arrival_time);
    }
}

bool Storage::isAdjacent(string name) {
    map<shared_ptr<Storage>,Weight>::iterator it;
    for (it = adjList.begin(); it != adjList.end(); it++) {
        if (name == it->first->getName()) return true;
    }
    return false;
}



