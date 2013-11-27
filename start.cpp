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
#define NTR 15

double LReal(double X, double Y) {
  return L(X,Y).real();
}

unsigned long long C[TS]; 
void PrecomputeC(){
  #pragma omp parallel for
  for(int i = 0; i < TS; i++){
    C[i] = choose(TS-1, i);
  }
}

double Euler(double T) {
  double SU[TS+1];
  
  const double A = 18.4;
  const int Ntr = NTR;
  const double U = exp(A/2)/T;
  const double X = A/(2*T);
  const double H = M_PI/T;

  double Sum = LReal(X,0)/2;
  double PS1[NTR+1];
  SU[0] = 0;
  double PS2[TS+1];

  #pragma omp parallel for
  for(int N = 1; N <= Ntr; N++){
    double Y = N*H;
    PS1[N] = pow((-1), N)*LReal(X,Y);
  }

  #pragma omp parallel for
  for (int N = 0; N < TS; N++)
  {
    int K = Ntr + N + 1;
    double Y = K * H;
    PS2[N] = pow((-1), K) * LReal(X,Y);
  }

  #pragma omp parallel for reduction(+:Sum)
  for(int N = 1; N <= Ntr; N++){
    Sum += PS1[N];
  }

  for(int K = 0; K < TS; K++){
    SU[K+1] = SU[K] + PS2[K];
  }

  double Avgsu = 0;

  #pragma omp parallel for reduction(+:Avgsu)
  for(int j = 0; j < TS; j++) {
    Avgsu += (C[j]*Sum + C[j]*SU[j+1]);
  }

  return U*Avgsu/2048;
}

int main() {
  PrecomputeC();
  cout << "Welcome, agent(s)! Best of luck." << endl;
  cout << "[";
  
  // Each of these is also fully independent, so could be run on a separate server
  // And collected + sorted after all of them finish
  for(int j = 0; j < 1; j++){
    double E[TS+1];

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
