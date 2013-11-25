#include<iostream>
#include "choose.h"

using namespace std;

unsigned long long choose(unsigned n, unsigned k){
  unsigned long long r = 1;
  if(k > n) return 0;
  for(unsigned d=1;d<=k;d++){
    r *= n--;
    r /= d;
  }

  return r;
}

/*
>>>>>>> granularity
int main(){
  int k;
  cin >> k;
  cout << "unsigned long long C[] = {";
  unsigned long long t = 1;
  for(int i = 0; i <= k; i++){
    cout << choose(k, i) << ", ";
  }
  cout << "};";
}
<<<<<<< HEAD

=======
*/
