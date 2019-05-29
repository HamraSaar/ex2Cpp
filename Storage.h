//
// Created by Admin on 5/24/2019.
//

#ifndef TRANSFERHB_STORAGE_H
#define TRANSFERHB_STORAGE_H

#include <string>
#include <map>
#include <ostream>
#include <memory>

#include "Weight.h"

using namespace std;

class Storage {
private:
    string name;
    int boxAmount;
    map<shared_ptr<Storage>,Weight> adjList;
public:
    Storage() = default;

    Storage(const string &name, int boxAmount);

    Storage(const Storage& other) = default;

    Storage& operator=(Storage& rhs);

    virtual ~Storage();

    const string &getName() const;

    void setName(const string &name);

    int getBoxAmount() const;

    void setBoxAmount(int boxAmount);

    const map<shared_ptr<Storage>, Weight> &getAdjList() const;

    void setAdjList(const map<shared_ptr<Storage>, Weight> &adjList);

    friend ostream &operator<<(ostream &os, const Storage &storage);

    void addNeighbor(shared_ptr<Storage> neighbor, Weight,string,string);

    bool operator==(const Storage &rhs) const;

    bool operator!=(const Storage &rhs) const;

    int getBoxCount(string time);

    bool isAdjacent(string);

};


#endif //TRANSFERHB_STORAGE_H
