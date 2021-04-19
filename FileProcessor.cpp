#include "FileProcessor.h"

FileProcessor::FileProcessor(){
    currLine = 0; //start with line 0
    currStu = 0;

    numMedians = 0;
    numIdleTimes = 0;
    numWindows = 0;

    timeOfEntry = 0;
    timeNeeded = 0;
}

FileProcessor::~FileProcessor() {
  delete [] arrayOfMedians;
  delete [] seqWindows; //deleting our arrays
  delete [] arrayOfIdleTimes;
}

bool FileProcessor::ProcessFile(string fileInput) {
	inFS.open(fileInput); //syntax to open the file
	if (inFS.is_open()) { //if everything opens and works
    getline(inFS, fileSentence); //read the first line
    numWindows = stoi(fileSentence); //since we know the first line symbolizes the number of windows, we initialize that
    seqWindows = new Student*[numWindows]; //we create our array of type Student* here

    for (int i = 0; i < numWindows; ++i) { //assign some empty value to our windows
        Student* s = new Student();
        seqWindows[i] = s;
    }

    while (getline(inFS, fileSentence)) { //while a line exists
        switch (currLine) {
            case (0): { //if the number is 0, that means the input is the tick number
                timeOfEntry = stoi(fileSentence); //
                currLine++; //increment our currLine
                break;
            }
            case (1): { //if the number is 1, it's the number of students at the given time
              if (fileSentence != "") {
                currStu = stoi(fileSentence);
              }

              for (int i = 0; i < currStu; ++i) { //run a for loop the number of students there are
                getline(inFS, fileSentence); //read the next line
                timeNeeded = stoi(fileSentence); //get the time needed for that respective student
                Student* s1 = new Student(timeNeeded, timeOfEntry); //create a new student with its new data
                sGenQueue.Enqueue(s1); //enqueue the student to the student queue
              }

              currLine = 0; //reset the currLine to 0
              break;
            }
            default:
              break;
        }
    }
  }
  return true;
}

int FileProcessor::LongestWaitingTime(){
    if (numMedians > 0) { //because arrayOfMedians is sorted from least to greatest, the last index will be the greatest number
        return arrayOfMedians[numMedians - 1];
    }
}

double FileProcessor::MeanStudentTime(){
    ListNode<int> *curr = waitTimeList.returnListNode(); //setting our ListNode curr equal to the front node of waitTimeList

    int objectCount = 0;
    int total = 0;

    double meanWaitingTime = 0;

    while (curr != NULL) {
        total += curr->data; //getting the sum
        curr = curr->next; //moving on to next node
        objectCount++; //counting total number of nodes
    }

    meanWaitingTime = double(total) / double(objectCount); //average is sum/total number of nodes
    return meanWaitingTime;
}

int FileProcessor::TotalWaitsAboveTen(){
    int returnNum = 0;
    for (int i = 0; i < numMedians; ++i) {
        if (arrayOfMedians[i] > 10) { //if any wait time is above 10 minutes, we mark it and return the total number
            returnNum++;
        }
    }
    return returnNum;
}

double FileProcessor::MeanWindowIdleTime(){
    ListNode<int> *curr = idleTimeList.returnListNode(); //setting curr equal to the front node of our idleTime List

    int total = 0;
    int objectCount = 0;

    double meanWindowIdleTime = 0;

    while (curr != NULL){
        total += curr->data;
        curr = curr->next;
        objectCount++;
    }

    meanWindowIdleTime = double(total) / double(objectCount); //same process as the above function but for a different queue
    return meanWindowIdleTime;
}

int FileProcessor::LargestIdleTime(){
    ListNode<int> *curr = idleTimeList.returnListNode();

    numIdleTimes = 0;
    while (curr != NULL){
        curr = curr->next;
        numIdleTimes++; //total number of idle times
    }

    curr = idleTimeList.returnListNode();
    arrayOfIdleTimes = new int[numIdleTimes]; //initalizing the array
    for (int i = 0; i < numIdleTimes; ++i){
        arrayOfIdleTimes[i] = curr->data; //filling the array with data
        curr = curr->next;
    }
    sort(arrayOfIdleTimes, arrayOfIdleTimes + numIdleTimes); //sorting the data from least to greatest
    return (arrayOfIdleTimes[numIdleTimes - 1]); //returning the last index because it's the greatest value
}

int FileProcessor::TotalIdleTimesAboveFive() {
    int returnNum = 0;
    for (int i = 0; i < numIdleTimes; ++i){
        if (arrayOfIdleTimes[i] > 5) { //if any index of the array has an int greater than 5 it will be marked
            returnNum++;
        }
    }
    return returnNum;
}

double FileProcessor::MedianStudentWait() {
    ListNode<int> *curr = waitTimeList.returnListNode();

    numMedians = 0;
    double medianWaitingTime = 0;

    while (curr != NULL) {
        curr = curr->next;
        numMedians++; //counts number of elements in queue
    }

    curr = waitTimeList.returnListNode();
    arrayOfMedians = new int[numMedians]; //creates array
    for (int i = 0; i < numMedians; ++i) {
        arrayOfMedians[i] = curr->data;
        curr = curr->next; //putting data into the array
    }

    sort(arrayOfMedians, arrayOfMedians + numMedians); //sorting it from least to greatest
    if (numMedians % 2 == 0) { //if there is an even number of elements, we must find the average of the middle two numbers
        int firstNum = 0;
        int secondNum = 0;

        firstNum = numMedians / 2;
        secondNum = (numMedians / 2) + 1;

        medianWaitingTime = double(arrayOfMedians[firstNum]) / double(arrayOfMedians[secondNum]); //simple enough
        return medianWaitingTime;
    }

    else { //if it's an odd number of elements, find the middle index
        int arraySize = 0;
        double returnNum = 0;

        arraySize = (numMedians / 2) + 1;
        returnNum = arrayOfMedians[arraySize];
        return returnNum;
    }
}

void FileProcessor::AddTime(int currStu) { //method to increment the time
    for (int i = 0; i < numWindows; ++i) {
        if (seqWindows[i]->timeSpentAtWindow > 0) { //if the time needed at the window is still greater than 1
            seqWindows[i]->timeSpentAtWindow--; //decrement it by 1
        }
        else{
            seqWindows[i]->timeSpentIdle++; //if they're not at the window, increment the idle time
        }
    }

    if (!sGenQueue.isEmpty()) {
        ListNode<Student*> *curr = sGenQueue.returnListNode();
        while (curr != NULL) {
             if (curr->data->timeOfEntry < currStu) {
                curr->data->timeSpentInQueue += 1; //increment the time in the queue by 1
             }
             curr = curr->next; //move to next node
        }
    }
}
