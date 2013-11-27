#include <iostream>
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
