#include <iostream>
#include <complex>
#include <cmath>
#include <cstdio>
#define _USE_MATH_DEFINES
#include <math.h>
#include <mpi.h>

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

  int head = 1;
  
  //rank is the iteration of euler
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  
  // Each of these is also fully independent, so could be run on a separate server
  // And collected + sorted after all of them finish
  //for(int j = 0; j < 10; j++)
  double result = Euler(rank);
  double *results;
  int size;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  if (rank == head){
    double allocation[size];
    //results = (double *)malloc(size*sizeof(double));
    results = allocation;
  }

  MPI_Gather( &result, 1, MPI_DOUBLE, results, size, MPI_DOUBLE, head, MPI_COMM_WORLD); 
  //(&result, MPI_DOUBLE, head, MPI_ANY_TAG, MPI_COMM_WORLD);

  MPI_Finalize();

  return 0;
}
