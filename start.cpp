#include <iostream>
#include <complex>
#include <cmath>
#include <cstdio>
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
  int totalC = 2048;

  double A = 18.4;
  int Ntr = 15;
  double U = exp(A/2)/T;
  double X = A/(2*T);
  double H = M_PI/T;

  double Sum = LReal(X,0)/2;
  double PS1[16];
  SU[0] = 0;
  double PS2[13];

  #pragma omp parallel for
  for(int N = 0; N <= Ntr; N++){
    if(N > 0){
      double Y = N*H;
      PS1[N] = pow((-1), N)*LReal(X,Y);
    }
    if(N < 12){
      int K = Ntr + N + 1;
      double Y = K * H;
      PS2[N] = pow((-1), K) * LReal(X,Y);
    }
  }

  for(int N = 1; N <= Ntr; N++){
    Sum += PS1[N];
  }
  for(int K = 0; K < 12; K++){
    SU[K+1] = SU[K] + PS2[K];
  }

  double Avgsu = 0;
  for(int j = 0; j < 12; j++) {
    Avgsu += totalC*Sum + C[j]*SU[j];
  }

  double Fun = U*Avgsu/totalC;

  return Fun;
}

int main() {

  cout << "Welcome, agent(s)! Best of luck." << endl;
  cout << "[";
  
  // Each of these is also fully independent, so could be run on a separate server
  // And collected + sorted after all of them finish
  for(int j = 0; j < 10; j++){
    double E[13];

    #pragma omp parallel for
    for(int i = 0; i<= 12; i++){
      E[i] = Euler(i);
    }

    for(int i = 0; i <= 12; i++) {
      cout << E[i] << ", ";
    }
  }
  cout <<"]" << endl;
  return 0;
}
