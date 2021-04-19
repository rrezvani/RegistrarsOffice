#ifndef FILE_PROCESSOR_H
#define FILE_PROCESSOR_H

#include "GenQueue.h"
#include "Student.h"
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm> //including this for a specific method in the .cpp file
#include <array>

using namespace std;

class FileProcessor {
    private:
        int currLine; //variables to be used
        int currStu;
        int timeOfEntry;
        int timeNeeded;
        int numIdleTimes;
        int numMedians;

        ifstream inFS;
        string fileSentence;

    public:
        FileProcessor();
        ~FileProcessor();

        int LargestIdleTime();
        int TotalIdleTimesAboveFive();
        int LongestWaitingTime();
        int TotalWaitsAboveTen();

        bool ProcessFile(string userFile);
        
        void AddTime(int currTime);

        double MeanStudentTime();
        double MedianStudentWait();
        double MeanWindowIdleTime();

        GenQueue<Student*> sGenQueue; //queue of type Student* to add/remove students from
        GenQueue<int> waitTimeList; //queue of ints that store our waiting time
        GenQueue<int> idleTimeList; //queue of ints that store our idle time

        int *arrayOfMedians; //dynamically allocated array of the median wait times
        int *arrayOfIdleTimes; //dynamically allocated array of the idle times
        Student* *seqWindows; //dynamically array of type Student*

        int numWindows;
};

#endif
