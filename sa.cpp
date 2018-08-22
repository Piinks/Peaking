// Kate Lovett
// sa.cpp
// October 2017
// Simulated Anealing Hill-Climbing Algorithm

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include "SumofGaussians.h"

using namespace std;

int main(int argc, char* argv[]) {

  int seed = atoi(argv[1]);
  int D = atoi(argv[2]);
  int N = atoi(argv[3]);
  double TOLERANCE = .00000001; 	// *** Adjusting the tolerance here can yield different results

  double location[D];
  double newLocation[D];
  double dz[D];

  double temp = 200000000;			// *** Adjusting the temp here can yield different results
  double acceptableP = .75;
  double p, sEval, nEval, diff;
  bool accepted = false;
  int sign;

  srand(seed);
  SumofGaussians sog(D, N);


  // Set starting location
  for(long i = 0; i < D; i ++){
	 location[i] = (rand() % 10);
	 cout << setprecision(8)<< scientific << fixed << location[i] << ' ';
  }
  cout << sog.eval(location) << endl;

  // Here we go!
  for(int i = 0; i < 100000; i++){
	  //cout << "I= " << i << endl;

	  // Greedy climb to finish after cooling --------------------------
	  if(temp < TOLERANCE){
		  //cout << "Greedy";
		  sEval = sog.eval(location);
		  sog.deriv(location, dz);
		  for(int k = 0; k < D; k++){
			  location[k] = location[k] + 0.01*dz[k];
			  cout << location[k] << ' ';
		  }
		  cout << sog.eval(location) << endl;
		  nEval = sog.eval(location);
		  if((nEval - sEval) < TOLERANCE){
			  // Printing out final location for collecting stats
			  //cout << sog.eval(location) << endl;
			  return 0;
		  }
	  }

	  // Simulated Annealing -------------------------------------------
	  else{
		  // Update temp
		  temp *= .999;
		  // Get next step. This will be a value between -0.01 and 0.01
		  for(int j = 0; j < D; j++){
			  // I could not get runif to work properly, so I created my own
			  //newLocation[j] = location[j] + runif(-0.01, 0.01);
			  int rpoint;
			  if((location[j] < 10) && (location[j] > 1)){
				  rpoint = rand() % 2000 -1000;
			  }
			  else if (location[j] >= 10){
				  rpoint = rand() % 1000 -1000;
			  }
			  else{
				  rpoint = -1 * (rand() % 1000 -1000);
			  }
			  newLocation[j] = location[j] + (rpoint/100000.0);
		  }

		  // Evaluate and compare new location to current,
		  // if it is better, accept it.
		  if(sog.eval(newLocation) > sog.eval(location)){
			  accepted = true;
		  }

		  // If not, accept based on probability
		  else{
			  p = exp(((sog.eval(newLocation)-sog.eval(location))/temp));
			  if(p >= acceptableP){
				  accepted = true;
			  }
		  }

		  // If this move has been accepted, update location.
		  if(accepted){
			  // Update our current location to the new one
			  for(int k = 0; k < D; k++){
				  location[k] = newLocation[k];
				  cout << location [k] << ' ';
			  }
			  cout<< sog.eval(location) << endl;
		  }
		  accepted = false;
	  }
  }
  // Printing out final location for collection of stats
  //cout << sog.eval(location) << endl;

  return 0;
}
