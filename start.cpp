#include <iostream>
#include <complex>
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

#include "mystery.h"

double L2(double X, double Y){
  complex<double> S (X, Y);
  double Rho = 0.75;
  double Mean = 1;
	
  complex<double> Gs = 1.0/sqrt(1.0 + 2.0 * S);
  complex<double> Gse = (1.0 - Gs)/(Mean*S);
  complex<double> Fs = (1.0 - Gse)/(S*(1.0 - Rho*Gse));
	
  double Rfs = Fs.real();
  return Rfs;
}

double LReal(double X, double Y) {
  return L(X,Y).real();
}

double Euler(double T) {
  double SU[13];
  int C[] = {1,11,55,165,330,462,462,330,165,55,11,1};

  double A = 18.4;
  int Ntr = 15;
  double U = exp(A/2)/T;
  double X = A/(2*T);
  double H = M_PI/T;

  double Sum = LReal(X,0)/2;
  for(int N = 1; N <= Ntr; N++) {
    double Y = N*H;
    Sum += pow((-1),N)*LReal(X,Y);
  }

  SU[0] = Sum;
  for(int K = 0; K < 12; K++) {
    int N = Ntr + K+1;
    double Y = N*H;
    SU[K+1] = SU[K] + pow((-1), N)*LReal(X,Y);
  }

  double Avgsu1 = 0;
  for(int j = 0; j < 12; j++) {
    Avgsu1 += C[j]*SU[j+1];
  }

  double Fun1 = U*Avgsu1/2048;

  return Fun1;

}

int main() {

  cout << "Welcome, agent(s)! Best of luck." << endl;
  //Euler();
  
  //time_t  timev;
  //time(&timev);
  //double T = (double) timev;
//
  //Euler(T);
  cout << "[";
  for(int i = 1; i <= 12; i++) {
    cout << Euler(i) << ", ";
  }
  cout <<"]" << endl;
  return 0;
}


