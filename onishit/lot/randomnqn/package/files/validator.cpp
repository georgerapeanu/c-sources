#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

const int NMAX = 500;
const int MMAX = 1000000009;

bool isPrime(int m){
  if(m < 2){
    return true;
  }
  for(int i = 2;1LL * i * i <= m;i++){
    if(m % i == 0){
      return false;
    }
  }
  return true;
}

int main(int argc, char **argv){
  registerValidation(argc, argv);
  int n = inf.readInt(1, NMAX,"n");
  inf.readSpace();
  int m = inf.readInt(1, MMAX,"m");
  inf.readEoln();
  inf.readEof();

  ensuref(isPrime(m), "modulo must be prime"); 

  return 0;
}


