#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char **argv){
  registerValidation(argc, argv);
  int n = inf.readInt(1, 5000,"n");
  inf.readSpace();
  int k = inf.readInt(1, n, "k");
  inf.readEoln();
  vector<int> perm(n, 0);
  vector<int> l(k, 0);

  for(int i = 0;i < n;i++){
    perm[i] = inf.readInt(1, n, "p_i");
    if(i + 1 < n){
      inf.readSpace();
    }
  }
  inf.readEoln();

  for(int i = 0;i < k;i++){
    l[i] = inf.readInt(1, n, "l_i");
    if(i + 1 < k){
      inf.readSpace();
    }
  }
  inf.readEoln();
  inf.readEof();

  sort(perm.begin(), perm.end());
  sort(l.begin(), l.end());

  for(int i = 1;i < (int)l.size();i++){
    if(l[i - 1] == l[i]){
      ensuref(false, "Lengths not distinct!");
    }
  }
  
  for(int i = 0;i < (int)perm.size();i++){
    if(perm[i] != i + 1){
      ensuref(false, "Order is not permutation");
    }
  }

  return 0;
}
