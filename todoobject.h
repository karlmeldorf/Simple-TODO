#ifndef TODOOBJECT_H
#define TODOOBJECT_H

#include <iostream>
#include <string>
#include <ctime>
#include <list>
#include <time.h>
#include <vector>

using namespace std;

class todoObject
{
public:
    string name;
    time_t dateTime;
    vector<bool> progress;
    vector<string> tasks;

    todoObject(string _name);

    ~todoObject() {}

    void addTask(string task);

    string getDateString();

    int getProgressNumber();

    string getProgress();
};

#endif // TODOOBJECT_H
