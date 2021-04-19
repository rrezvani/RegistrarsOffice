#include "Simulation.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
  Simulation simulation; //creating an instance of our simulation class

  simulation.simulate(argc, argv[1]); //calling the simulate function which carries out the main program
  return 0;
}
