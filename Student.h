#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>

using namespace std;

class Student {
    private:

    public:
        Student();
        ~Student();
        Student(int tAW, int eT); //timeAtWindow and entryTime are the parameters

        int timeSpentInQueue; //public variables that will be called elsewhere
        int timeSpentAtWindow;
        int timeSpentIdle;
        int timeOfEntry;
};

#endif
