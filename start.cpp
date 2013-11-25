#include <iostream>
#include <complex>
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

#include "mystery.h"

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

  // Can be refactored to Map -> Reduce
  //
  // #1 Map - fully independent
  // PS1[Ntr+1];
  // for(int N = 1; N <= Ntr; N++){
  //	double Y = N*H;
  // 	PS1[N] = poq((-1), N)*LReal(X, Y);
  // }
  //
  // #2 Reduce - sequential
  // Sum = sum(PS1);

  SU[0] = 0;
  
  for(int K = 0; K < 12; K++) {
    int N = Ntr + K+1;
    double Y = N*H;
    SU[K+1] = (SU[K] + pow((-1), N)*LReal(X,Y));
  }
  
  //Can be refactored to
  //
  // #1 Map - fully independent, each run only needs to know H and X
  //
  // double PS[13]
  // for(int K = 0; K < 12; K++){
  //	int N = Ntr + K + 1;
  //	double Y = N * H;
  //	PS[K] = pow((-1), N) * LReadl(X,Y);
  // }
  //
  // #2 Sequential Reduce - fully sequential
  // #3 Parallel - could be turned into fully independent by
  // distributing PS and Sum to all of the process and collecting the result:
  // SU[1] = Sum + PS[0]
  // SU[2] = Sum + PS[0] + PS[1]
  // SU[3] = Sum + PS[0] + PS[1] + PS[2]
  // 
  // for(int K = 0; K < 12; k++){
  //  SU[K+1] = SU[K] + PS[K];
  // }
  
  // This is where computations of Fun and Fun1 could be done independantly
  // They could diverge onto two different thingies
  double Avgsu = 0;
  
  for(int j = 0; j < 12; j++) {
    Avgsu += C[j]*Sum + C[j]*SU[j];
  }

  // Can be refactored to
  //
  // CS[2][13]
  //
  // # Fully independent loop - map
  // for(int j = 0; j < 12; j++){
  // 	CS[0][j] = C[j] * SU[j];
  // }
  //
  // # Fully independent loop - map
  // # Each process requires to know only C[j] and Su[j+1]
  // for(int j = 0; j < 12; j++){
  //	CS[1][j] = C[j]*SU[j+1];
  // }
  //
  // # Reduce - fuly sequential
  // Avgsu = sum(CS[0]);
  // Avgsu1 = sum(CS[1])
  
  
  double Fun = U*Avgsu/2048;
  
  // This is where Fun and Fun1 have to converge

  return Fun;

}

int main() {

  cout << "[";
  
  // Each of these is also fully independent, so could be run on a separate server
  // And collected + sorted after all of them finish
  for(int i = 0; i <= 12; i++) {
    cout << Euler(i) << ", ";
  }
  cout <<"]" << endl;
  return 0;
}
