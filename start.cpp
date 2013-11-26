#include <iostream>
#include <complex>
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>
#include <mpi.h>

using namespace std;

#include "mystery.h"

#define TS 1200
#define M 11
#define Ntr 1500

double LReal(double X, double Y) {
  return L(X,Y).real();
}

double Euler(double T) {
  double SU[13];
  int C[] = {1,11,55,165,330,462,462,330,165,55,11,1};

  double A = 18.4; //accurate enough
  double U = exp(A/2)/T;
  double X = A/(2*T);
  double H = M_PI/T;

  //distribute between Ntr processors and reduce
  double Sum = LReal(X,0)/2;
  for(int N = 1; N <= Ntr; N++) {
    double Y = N*H;
    Sum += pow((-1),N)*LReal(X,Y);
  }

  //dynamic program into SU and reduce using the current loop
  SU[0] = 0;
  for(int K = 0; K < M; K++) {
    int N = Ntr + K+1;
    double Y = N*H;
    SU[K+1] = SU[K] + pow((-1), N)*LReal(X,Y);
  }

  double Avgsu1 = 0;
  for(int j = 0; j < M; j++) {
    Avgsu1 += C[j]*Sum + C[j]*SU[j+1];
  }

  double Fun1 = U*Avgsu1/2048;

  return Fun1;

}

int main() {

  cout << "Welcome, agent(s)! Best of luck." << endl;

  if(MPI_Init(NULL,NULL) != MPI_SUCCESS) {
    return -1;
  }

  int head = 0;

  int rank, size;

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  double ts[TS];// = {1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0,11.0,12.0};

  for(int i = 0; i <= TS; i++) {
    ts[i] = (12.0*(i+1))/TS;
  }
  double results[TS];

  int t_len = TS/size;

  double t[t_len];

  //scatter
  MPI_Scatter(&ts, t_len, MPI_DOUBLE, &t, t_len, MPI_DOUBLE, head, MPI_COMM_WORLD);

  cout << "t: "<<t << endl;

  double localResults[t_len];
  // cout << *t << endl;
  cout << t_len << endl;
  for(int i = 0; i < t_len; i++) {
    double result = Euler(t[i]);
    localResults[i] = result;
    cout << "(" << rank << ", " << i << ")" << endl;
  }

  MPI_Gather(&localResults, t_len, MPI_DOUBLE, rank == head ? results : NULL, t_len, MPI_DOUBLE, head, MPI_COMM_WORLD); 

  if (rank == head){
    cout << '[';
    for(int i = 1; i <= TS; ++i){
      cout << results[i] << ", ";
    }
    cout << ']' << endl;
  }

  MPI_Finalize();

  // cout << "[";
  // for(int i = 1; i <= 12; i++) {
  //   cout << Euler(i) << ", ";
  // }
  // cout <<"]" << endl;
  return 0;

}
