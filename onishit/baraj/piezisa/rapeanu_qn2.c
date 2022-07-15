#include "piezisa.h"
#include <stdlib.h>

const int LEN = 2;

void solve(int n, int v[], int q, int l[], int r[], int solutions[]){
  
  int* prefix_xors = (int*)malloc((n + 1) * sizeof(int));
  prefix_xors[0] = 0;

  for(int i = 1;i <= n;i++){
    prefix_xors[i] = v[i - 1] ^ prefix_xors[i - 1];
  }

  for(int h = 0;h < q;h++){
    int ans = 1e9;
    for(int i = l[h] + 1;i;i--){
      for(int j = r[h] + 1;j <= n;j++){
        if(prefix_xors[j] == prefix_xors[i - 1]){
          if(j - i + 1 < ans){
            ans = j - i + 1;
          }
        }
      }
    }
    if(ans == 1e9){
      ans = -1;
    }
    solutions[h] = ans;
  }
  free(prefix_xors);
}

