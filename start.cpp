#include <iostream>
#include <complex>
#include <cmath>

using namespace std;

#include "mystery.h"

complex<double> L2(double X, double Y){
  complex<double> S (X, Y);
  double Rho = 0.75;
  double Mean = 1;
	
  complex<double> Gs = 1.0/sqrt(1.0 + 2.0 * S);
  complex<double> Gse = (1.0 - Gs)/(Mean*S);
  complex<double> Fs = (1.0 - Gse)/(S*(1.0 - Rho*Gse));
	
  double Rfs = Fs.real();
  return Fs;
}

int main() {

  cout << "Welcome, agent(s)! Best of luck." << endl;
  cout << L(1,1) << endl;
  cout << L(1,1) << endl;
  cout << L(1,1) << endl;
  cout << L(1,1) << endl;
  cout << L(1,1) << endl;
  cout << L2(1,1) << endl;


  return 0;
}


