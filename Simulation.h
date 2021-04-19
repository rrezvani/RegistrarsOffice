#ifndef SIMULATION_H
#define SIMULATION_H

#include <iostream>
#include "FileProcessor.h"
#include "Student.h"

using namespace std;

class Simulation {
  public:
    Simulation(); //constructor
    ~Simulation(); //destructor
    void simulate(int numInputs, string inputFile); //simulate function that carries out the whole program, takes in the number of inputs and the argv[1] variable which should be a file

  private:
    int numAvailableWindows;
    int currTime;
    bool keepRunning;
    FileProcessor fileProcessor; //instance of our fileprocessor class
};

#endif
