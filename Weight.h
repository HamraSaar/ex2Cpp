//
// Created by Admin on 5/25/2019.
//

#ifndef TRANSFERHB_WEIGHT_H
#define TRANSFERHB_WEIGHT_H

#include <iostream>
#include <ctime>
#include <vector>
using namespace std;

struct TruckDetails {
    string departure_time;
    string arrival_time;
    int boxAmount;
};

class Weight {
private:
    int boxAmount;
    double minutes;
    int trucksAmount;
    vector<TruckDetails> trucksDetails;
    struct tm parseTime(string str) {
        int day,month,hours,minutes;
        std::string::size_type sz;
        day = stoi(str.substr(0,2),&sz);
        month = stoi(str.substr(3,5),&sz);
        hours = stoi(str.substr(6,8),&sz);
        minutes = stoi(str.substr(9,11),&sz);

        time_t raw;
        time(&raw);
        struct tm t1 = *gmtime(&raw);

        t1.tm_year = 2019 - 1900;
        t1.tm_mon = month - 1;
        t1.tm_mday = day;
        t1.tm_hour = hours;
        t1.tm_min = minutes;
        t1.tm_sec = 0;

        return t1;
    }

    int calcMinutes(string time1, string time2) {
        struct tm t1 = parseTime(time1);
        struct tm t2 = parseTime(time2);

        time_t tt1, tt2;
        tt1 = mktime(&t1);
        tt2 = mktime(&t2);

        return (tt2 - tt1)/60;
    }

public:
    Weight() : boxAmount(0),minutes(0),trucksAmount(0) {}
    Weight(int boxAmount, string departure_time, string arrival_time) : boxAmount(boxAmount), trucksAmount(1) {
        //calculate minutes
        minutes = calcMinutes(departure_time,arrival_time);
        TruckDetails td;
        td.boxAmount = boxAmount;
        td.departure_time = departure_time;
        td.arrival_time = arrival_time;
        trucksDetails.push_back(td);
    }

    void addTruck(int min, int boxes, string departure_time, string arrival_time) {
        boxAmount += boxes;
        trucksAmount++;
        minutes = ((minutes*(trucksAmount-1)) + min) / trucksAmount;
        //add truck to list
        TruckDetails td;
        td.boxAmount = boxes;
        td.departure_time = departure_time;
        td.arrival_time = arrival_time;
        trucksDetails.push_back(td);
    }

    int getArrivalBoxCount(string time) {
        int boxCount = 0;
        vector<TruckDetails>::iterator it;
        for (it = trucksDetails.begin(); it != trucksDetails.end(); it++) {
            int minutes = calcMinutes(it->arrival_time,time);
            if (minutes >=0) boxCount += it->boxAmount;
        }
        return boxCount;
    }

    int getDepartureBoxCount(string time) {
        int boxCount = 0;
        vector<TruckDetails>::iterator it;
        for (it = trucksDetails.begin(); it != trucksDetails.end(); it++) {
            int minutes = calcMinutes(it->departure_time,time);
            if (minutes >= 0) boxCount += it->boxAmount;
        }
        return boxCount;
    }

    int getMinMinutes() {
        int minMinutes = INTMAX_MAX;
        vector<TruckDetails>::iterator it;
        for (it = trucksDetails.begin(); it != trucksDetails.end(); it++) {
            int tmp = calcMinutes(it->departure_time,it->arrival_time);
            if (minMinutes < tmp) minMinutes = tmp;
        }
        return minMinutes;
    }

    int getBoxAmount() const {
        return boxAmount;
    }

    double getMinutes() const {
        return minutes;
    }

    int getTrucksAmount() const {
        return trucksAmount;
    }
};

#endif //TRANSFERHB_WEIGHT_H

