// Kate Lovett
// greedy.cpp
// October 2017
// Greedy Hill-climbing Algroithm

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "SumofGaussians.h"

using namespace std;

int main(int argc, char* argv[]) {

  int seed = atoi(argv[1]);
  int D = atoi(argv[2]);
  int N = atoi(argv[3]);
  double TOLERANCE = .00000001;

  double location[D];
  double dz[D];
  double sEval, nEval, diff;

  srand(seed);
  SumofGaussians sog(D, N);

  // Set starting location
  for(int i = 0; i < D; i ++){
	 location[i] = (rand() % 10);
	 cout << setprecision(8)<< scientific << fixed << location[i] << ' ';
  }
  cout << sog.eval(location) << endl;

  // Initialize first potential move before while loop
  sEval = sog.eval(location);
  sog.deriv(location, dz);
  for(int i =0; i < D; i ++){

	  // Here, and in the following while loop, the derivative
	  // of each point is evaluated individually to determine the step.
	  // A tep will be taken in the direction of ascent.
	  // This works because a negative slope will result in going
	  // in the opposite direction when adding to the current point.
	  location[i] = location[i] + 0.01*dz[i];
  }

  nEval = sog.eval(location);

  // Diff is the evaluated increase of the function, which will
  // control the while loop below. Once the diff drops below the
  // designated tolerance, ascent stops.
  diff = nEval - sEval;


  // Begin to climb
  while(diff > TOLERANCE){
	  for(int i = 0; i < D; i ++){
		  cout << location[i] << ' ';
	  }
	  cout << sog.eval(location) << endl;

	  sEval = sog.eval(location);
	  sog.deriv(location, dz);
	  for(int i =0; i < D; i ++){
		  location[i] = location[i] + 0.01*dz[i];
	  }
	  nEval = sog.eval(location);
	  diff = nEval - sEval;
  }
  // For testing purposes
  //cout << sog.eval(location) << endl;
  return 0;
}
