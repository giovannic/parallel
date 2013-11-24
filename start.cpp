#include <iostream>
#include <complex>
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>

#define len 20

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

unsigned long factorial(int n)
{
  return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

unsigned long bin(int n, int k) {
  return factorial(n)/(factorial(k)*factorial(n-k));
}

double Euler(double T) {
  //int C[len] = {1,11,55,165,330,462,462,330,165,55,11,1}
  int C[len];
  for(int i = 0; i < len; i++) {
    C[i] = bin(len-1, i);
  }

  double SU[len+1];

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
  for(int K = 0; K < len; K++) {
    int N = Ntr + K+1;
    double Y = N*H;
    SU[K+1] = SU[K] + pow((-1), N)*LReal(X,Y);
  }

  double Avgsu = 0;
  double Avgsu1 = 0;
  for(int j = 0; j < len; j++) {
    Avgsu += C[j]*SU[j];
    Avgsu1 += C[j]*SU[j+1];
  }

  double Fun = U*Avgsu/2048;
  double Fun1 = U*Avgsu1/2048;
  double err = abs(Fun-Fun1)/2;

  return Fun1;

}

int main() {

  cout << "Welcome, agents! Best of luck." << endl;
  //Euler();
  
  //time_t  timev;
  //time(&timev);
  //double T = (double) timev;
//
  //Euler(T);
  cout << "[";
  for(double i = 0; i <= 12.0; i+= 12.0/len) {
    cout << Euler(i) << ", ";
  }
  cout <<"]" << endl;

  for(int i = 0; i < len; i++) {
    cout << bin(len-1, i) << " ";
  }
  cout << endl;

  return 0;
}


