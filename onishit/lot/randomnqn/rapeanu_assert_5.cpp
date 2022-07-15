#include <bits/stdc++.h>
#include "ghinion.h"

using namespace std;

int add(int a, int b, int mod) {
  a += b;

  if(a >= mod){
    a -= mod;
  }

  return a;
}

int scad(int a, int b, int mod){
  a -= b;
  
  if(a < 0){
    a += mod;
  }

  return a;
}

int mult(int a, int b, int mod) {
  return 1LL * a * b % mod;
}


int solve(int n, int m){
    assert(n <= 500); 
    vector<int> pw2(n + 1, 0);
    pw2[0] = 1;
    for(int i = 1;i <= n;i++){
      pw2[i] = add(pw2[i - 1], pw2[i - 1], m);
    }

    vector<vector<int>> dp1(n + 1, vector<int>(n + 1, 0));
    for(int i = 1;i < n;i++){
      dp1[i][i] = 1;
      for(int j = 1;j <= i;j++){
        for(int k = 1;i + 1 + k <= n;k++){
          if(j < k){
            dp1[i + 1 + k][k] = add(dp1[i + 1 + k][k], mult(pw2[j], dp1[i][j], m), m);
          }else{
            dp1[i + 1 + k][j] = add(dp1[i + 1 + k][j], mult(pw2[k], dp1[i][j], m), m);
          }
        }
      }
    }

    for(int i = 1;i <= n;i++){
      for(int j = i - 1;j >= 1;j--){
        dp1[i][j] = add(dp1[i][j], dp1[i][j + 1], m);
      }
    }

    vector<vector<int> > dp2(n + 1, vector<int>(n + 1, 0));

   for(int i = 1;i < n;i++){
    for(int j = 1;j <= i;j++){
      dp2[i][j] = add(dp2[i][j], dp1[i][j], m);  
      for(int k = 1;i + 1 + k <= n;k++){
        dp2[i + 1 + k][j] = add(dp2[i + 1 + k][j], mult(dp1[k][j], dp2[i][j], m), m);
      }
    }
   }

   int ans = 0;

   for(int j = n;j >= 1;j--){
    for(int k = j + 1;k <= n;k++){
      dp2[n][j] = scad(dp2[n][j], dp2[n][k], m);
    }
    ans = add(ans, mult(dp2[n][j], pw2[j], m), m);
   }

   return ans;
}


