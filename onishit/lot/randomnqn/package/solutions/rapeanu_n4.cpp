#include <bits/stdc++.h>
#include "ghinion.h"

using namespace std;

int add(int a, int b, int mod){
  a += b;
  if(a >= mod){
    a -= mod;
  }
  return a;
}

int sub(int a, int b, int mod){
  a -= b;
  if(a < 0){
    a += mod;
  }
  return a;
}

int mult(int a, int b, int mod){
  return 1LL * a * b % mod;
}

int solve(int n, int m){

  vector<int> pw2(n + 1);
  pw2[0] = 1;

  for(int i = 1;i <= n;i++){
    pw2[i] = add(pw2[i - 1], pw2[i - 1], m);
  }
  vector<vector<vector<int>> > dp(n + 1, vector<vector<int>>(n + 1, vector<int>(2, 0)));
  vector<int> length_dp(n + 1, 0);

  for(int shortest_length = 1;shortest_length <= n;shortest_length++){
    for(int i = 0;i <= n;i++){
      for(int j = 0;j <= i;j++){
        dp[i][j][0] = dp[i][j][1] = 0;
      }
    }

    for(int i = 1;i < n;i++){
      dp[i][i][0] = 1; 
    }

    for(int i = 0;i <= n;i++){
      for(int j = 0;j <= i;j++){
        for(int k = 1;i + k + 1 <= n;k++){
          if(j >= k){
            dp[i + k + 1][j][1] = add(dp[i + k + 1][j][1], mult(dp[i][j][1], pw2[k], m), m);
            dp[i + k + 1][j][0] = add(dp[i + k + 1][j][0], mult(dp[i][j][0], pw2[k], m), m);
          }else{
            dp[i + k + 1][k][1] = add(dp[i + k + 1][k][1], mult(dp[i][j][1], pw2[j], m), m);
            dp[i + k + 1][k][0] = add(dp[i + k + 1][k][0], mult(dp[i][j][0], pw2[j], m), m);
          }
          if(i + 1 <= n && j >= shortest_length){
            dp[i + 1 + k][k][1] = add(dp[i + 1 + k][k][1], dp[i][j][1], m);
            dp[i + 1 + k][k][1] = add(dp[i + 1 + k][k][1], dp[i][j][0], m);
          }
        }
      }
    }
      

    for(int j = shortest_length;j <= n;j++){
      length_dp[shortest_length] = add(length_dp[shortest_length], dp[n][j][1], m);
    }
  }

  int ans = 0;

  for(int i = n;i >= 1;i--){
    for(int j = i + 1;j <= n;j++){
      length_dp[i] = sub(length_dp[i], length_dp[j], m);
    }
    ans = add(ans, mult(length_dp[i], pw2[i], m), m);
  }

  return ans;
}
