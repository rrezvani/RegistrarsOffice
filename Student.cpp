#include "Student.h"

Student::Student() {
    timeSpentInQueue = 0;
    timeSpentAtWindow = 0;
    timeSpentIdle = 0;
    timeOfEntry = 0;
}

Student::~Student(){

}

Student::Student(int tAW, int eT) { //overload constructor for custom data
    timeSpentAtWindow = tAW;
    timeOfEntry = eT;
    timeSpentIdle = 0;
    timeSpentInQueue = 0;
}
