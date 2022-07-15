#include "./testlib/testlib.h"
#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2e5;
const int QMAX = 5e5;
const int VMAX = (1 << 28) - 1;

int main(int argc, char **argv){
  registerValidation(argc, argv);
  int n = inf.readInt(1, NMAX,"n");
  inf.readEoln();

  for(int i = 0;i < n;i++){
    int value = inf.readInt(0,VMAX,"x");
    if(i < n - 1){
      inf.readSpace();
    }
  }
  inf.readEoln();
  int q = inf.readInt(1, QMAX,"q");
  inf.readEoln();
  for(int i = 0;i < q;i++){
    int l, r;
    l = inf.readInt(0,n - 1,"l_i");
    inf.readSpace();
    r = inf.readInt(l,n - 1,"r_i");
    inf.readEoln();
  }
  inf.readEof();

  return 0;
}


