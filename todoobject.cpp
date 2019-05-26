#include "todoobject.h"

#include <iostream>
#include <string>
#include <ctime>
#include <list>
#include <time.h>

using namespace std;

string name;
time_t dateTime;
list<bool> progress;
list<string> tasks;

todoObject::todoObject(string _name)
{
    name = _name;
    dateTime = time(0);
}

void todoObject::addTask(string task) {
    tasks.push_back(task);
    progress.push_back(false);
}

string todoObject::getDateString() {
    char buff[20];
    strftime(buff, 20, "%Y-%m-%d %H:%M:%S", localtime(&dateTime));
    return string(buff);
}

int todoObject::getProgressNumber() {
    int number = 0;
    for (bool state : progress) {
        if (state == true) {
            number += 1;
        }
    }
    return number;
}

string todoObject::getProgress() {
    string toReturn = to_string(getProgressNumber());
    toReturn += "/" + to_string(progress.size());
    return toReturn;
}
