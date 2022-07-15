#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

const int TMAX = 10000;
const long long KMAX = 1e18;
const int NMAX = 1e6;
const int VMAX = 1e9;

int main(int argc, char **argv){
  registerValidation(argc, argv);
  int t = inf.readInt(1, TMAX,"t");
  inf.readEoln();

  int total_n = 0;

  while(t--){
    int n = inf.readInt(1, NMAX, "n");
    inf.readSpace();
    long long k = inf.readLong(0, KMAX, "k");
    inf.readEoln();
    total_n += n;
    inf.ensuref(total_n <= NMAX, "the sum of n's should be less than %d", NMAX);
    for(int i = 1;i <= n;i++){
      int v = inf.readInt(0, VMAX, "v_i");
      if(i < n){
        inf.readSpace();
      }else{
        inf.readEoln();
      }
    }
  }
  inf.readEof();

  return 0;
}


