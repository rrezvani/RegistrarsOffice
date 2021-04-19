#include "Simulation.h"

Simulation::Simulation() {
  currTime = 0;
  numAvailableWindows = 0; //initializing our variables
  keepRunning = true;
}

Simulation::~Simulation() {

}

void Simulation::simulate(int numInputs, string inputFile) {
  if (numInputs == 2) { //makes sure there are two inputs

    if (fileProcessor.ProcessFile(inputFile)) { //since our processfile method returns a bool, if it's true this will enter the if statement
      while (keepRunning) { //using our bool as our while loop conditional

        if (fileProcessor.sGenQueue.isEmpty()) { //if the student queue is empty
          int numToAdd = 0;

          for (int i = 0; i < fileProcessor.numWindows; ++i) {

            if ((fileProcessor.seqWindows[i]->timeSpentAtWindow) == 0) { //means a window is empty
              numToAdd++;
            }
          }

          if (numToAdd == fileProcessor.numWindows) { //if the number of windows matches the number of empty windows, we stop the simulation
            keepRunning = false;
          }
        }

        for (int i = 0; i < fileProcessor.numWindows; ++i) {

          if (fileProcessor.seqWindows[i]->timeSpentAtWindow == 0 && !fileProcessor.sGenQueue.isEmpty()) { //check if the window is empty

            //if the student queue has students
          Student* stu = fileProcessor.sGenQueue.peek(); //get the first person in line

              if (stu->timeOfEntry <= currTime){ //make sure it is valid, can't have the students time of entry be greater than the time we are currently at

                if (fileProcessor.seqWindows[i]->timeSpentIdle != 0) { //if there idle time is not 0, we have to add it our timeSpentIdle list to accumulate it in our statistics
                  fileProcessor.idleTimeList.Enqueue(fileProcessor.seqWindows[i]->timeSpentIdle); //syntax to enqueue the time
                }

                fileProcessor.seqWindows[i] = fileProcessor.sGenQueue.Dequeue(); //removes the student because they are now being helped
                fileProcessor.waitTimeList.Enqueue(fileProcessor.seqWindows[i]->timeSpentInQueue); //adds however much time they were at the window to our waitTimeList
              }

          }
        }
        currTime++; //increment the currTime
        fileProcessor.AddTime(currTime); //increment the clock tick
      }

      for (int i = 0; i < fileProcessor.numWindows; ++i) {

        if (fileProcessor.seqWindows[i]->timeSpentIdle != 0) {
          fileProcessor.idleTimeList.Enqueue(fileProcessor.seqWindows[i]->timeSpentIdle); //count up the idle windows that had no students in them at the end
        }
      }

      cout << "1) Mean student wait time: " << fileProcessor.MeanStudentTime() << endl; //print the corresponding messages
      cout << "2) Median student wait time: " << fileProcessor.MedianStudentWait() <<  endl;
      cout << "3) Longest student wait time: " << fileProcessor.LongestWaitingTime() <<  endl;
      cout << "4) Number of students waiting over 10 minutes: " << fileProcessor.TotalWaitsAboveTen() << endl;
      cout << "5) Mean window idle time: " << fileProcessor.MeanWindowIdleTime() << endl;
      cout << "6) Longest window idle time: " << fileProcessor.LargestIdleTime() << endl;
      cout << "7) Number of windows idle for over 5 minutes: " << fileProcessor.TotalIdleTimesAboveFive() << endl;
      cout << "Thanks for simulating!" << endl;
    }
	}

  else {
    cout << "Where is the file input?" << endl;
  }
}
