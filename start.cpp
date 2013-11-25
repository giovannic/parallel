#include <iostream>
#include <complex>
#include <cmath>
#include <cstdio>
#define _USE_MATH_DEFINES
#include <math.h>
#include <mpi.h>

#define T_DIV 1

using namespace std;

#include "mystery.h"

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

  #pragma omp parallel for
  for(int N = 1; N <= Ntr; N++){
    double Y = N*H;
    PS1[N] = pow((-1), N)*LReal(X,Y);
  }

  for(int N = 1; N <= Ntr; N++){
    Sum += PS1[N];
  }
  SU[0] = 0;
  double PS2[13];

  #pragma omp parallel for
  for(int K = 0; K < 12; K++){
    int N = Ntr + K + 1;
    double Y = N * H;
    PS2[K] = pow((-1), N) * LReal(X,Y);
  }

  for(int K = 0; K < 12; K++){
    SU[K+1] = SU[K] + PS2[K];
  }
  
  double Avgsu = 0;
  double offset = totalC*Sum;
  
  for(int j = 0; j < 12; j++) {
    Avgsu += offset + C[j]*SU[j];
  }
  
  double Fun = U*Avgsu/totalC;
  
  return Fun;

}

int main() {

  if (MPI_Init(NULL, NULL) != MPI_SUCCESS){
    return -1;
  }

  int head = 0;
  
  //rank is the iteration of euler
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  //cout << "rank of " << rank << endl;

  int size;
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int t_length = (12/T_DIV) - 1;
  double ts [t_length];
  double *results;

  if (rank == head){
    double allocation[t_length];
    results = allocation;

    for (int i = 0; i < t_length; ++i){
      ts[i] = (i + 1) * T_DIV;
      cout << ts[i] << endl;
    }
  }

  double t;
  //scatter
  //TODO what if not divisible
  MPI_Scatter(&ts, t_length/size, MPI_DOUBLE, &t, t_length/size, MPI_DOUBLE, head, MPI_COMM_WORLD); 

  // Each of these is also fully independent, so could be run on a separate server
  double result = Euler(t);
  cout << result << endl;

  MPI_Gather(&result, t_length/size, MPI_DOUBLE, results, t_length, MPI_DOUBLE, head, MPI_COMM_WORLD); 

  if (rank == head){
    cout << '[';
    for(int i = 0; i < 12; ++i){
      cout << results[i] << ", ";
    }
    cout << ']' << endl;
  }

  MPI_Finalize();

  return 0;
}
