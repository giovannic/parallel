#include <iostream>
#include <complex>
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

#include "mystery.h"
#include "choose.h"

#define T_DIV 1
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
  for(int N = 1; N <= Ntr; N++) {
    double Y = N*H;
    Sum += pow((-1),N)*LReal(X,Y);
  }

  SU[0] = Sum;
  for(int K = 0; K < TS; K++) {
    int N = Ntr + K+1;
    double Y = N*H;
    SU[K+1] = SU[K] + pow((-1), N)*LReal(X,Y);
  }

  double Avgsu1 = 0;
  for(int j = 0; j < TS; j++) {
    Avgsu1 += C[j]*SU[j];
  }

  double Fun1 = U*Avgsu1/2048;

  return Fun1;

}

int main() {

  int t_length = TS/T_DIV - 1;

  cout << "[";
  for(int i = 0; i < t_length; i++) {
    cout << Euler((double)(i + 1) / T_DIV) << ", ";
  }
  cout <<"]" << endl;
  return 0;

}
