#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e6;
const int KMAX = 1e5;
const int QMAX = 1e6;
const int VMAX = 0x7fffffff;

int main(int argc, char **argv){
  registerValidation(argc, argv);
  int n = inf.readInt(1, NMAX, "n");
  inf.readSpace();
  int k = inf.readInt(1, NMAX, "k");
  inf.readEoln();

  for(int i = 1;i <= n;i++){
    int a = inf.readInt(0, VMAX, "a_i");
    if(i < n){
      inf.readSpace();
    }
  }
  inf.readEoln();

  int q = inf.readInt(1, QMAX);
  inf.readEoln();

  while(q--){
    int type = inf.readInt(0, 1);
    if(type == 0){
      inf.readEoln();
    }
    else{
      inf.readSpace();
      int pos = inf.readInt(1, n);
      inf.readSpace();
      int val = inf.readInt(0, VMAX);
      inf.readEoln();
    }
  }

  inf.readEof();
  return 0;
}


