#include "piezisa.h"
#include <bits/stdc++.h>
using namespace std;

const int LEN = 3;

void solve(int n, int v[], int q, int l[], int r[], int solutions[]){
  vector<int> prefix_xors(n + 1, 0);

  for(int i = 1;i <= n;i++){
    prefix_xors[i] = v[i - 1] ^ prefix_xors[i - 1];
  }

  for(int h = 0;h < q;h++){
    int ans = 1e9;
    for(int i = l[h] + 1;i;i--){
      for(int j = r[h] + 1;j <= n;j++){
        if(prefix_xors[j] == prefix_xors[i - 1]){
          ans = min(ans, j - i + 1);
        }
      }
    }
    if(ans == 1e9){
      ans = -1;
    }
    solutions[h] = ans;
  }
}

