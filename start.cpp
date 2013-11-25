#include <iostream>
#include <complex>
#include <cmath>
#include <cstdio>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

#include "mystery.h"
#include "choose.h"

#define TS 12

double LReal(double X, double Y) {
  return L(X,Y).real();
}

double Euler(double T) {
  double SU[13];
  unsigned long long C[TS]; 
  
  for(int i = 0; i < TS; i++){
    C[i] = choose(TS, i);
  }

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
  for(int K = 0; K < TS; K++){
    SU[K+1] = SU[K] + PS2[K];
  }

  double Avgsu = 0;
  for(int j = 0; j < TS; j++) {
    Avgsu += C[j]*Sum + C[j]*SU[j+1];
  }

  double Fun = U*Avgsu/2048;

  return Fun;
}

int main() {

  cout << "Welcome, agent(s)! Best of luck." << endl;
  cout << "[";
  
  // Each of these is also fully independent, so could be run on a separate server
  // And collected + sorted after all of them finish
  for(int j = 0; j < 1; j++){
    double E[13];

    #pragma omp parallel for
    for(int i = 0; i<= TS; i++){
      E[i] = Euler(12.0*(i+1)/TS);
    }

    for(int i = 0; i <= TS; i++) {
      cout << E[i] << ", ";
    }
  }
  cout <<"]" << endl;
  return 0;
}
