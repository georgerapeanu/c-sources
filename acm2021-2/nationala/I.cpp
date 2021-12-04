#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;
const int SIGMA = 'Z' - 'A' + 1;

int n;
string s;
int dp[205][205][205];

int add(int a,int b){
  a += b;
  if(a >= MOD){
    a -= MOD;
  }
  return a;
}

int scad(int a,int b){
  a -= b;
  if(a < 0){
    a += MOD;
  }
  return a;
}

int mult(int a,int b){
  return 1LL * a * b % MOD;
}

int main(){

  cin >> n;
  cin >> s;

  s = " " + s;

  dp[0][1][n] = 1;

  for(int i = 0;i <= n;i++){
    for(int l = 0;l <= n;l++){
      for(int r = n;r >= 0;r--){
        if(l <= r){
          if(l < r && s[l] == s[r]){
            dp[i][l + 1][r - 1] = add(dp[i][l + 1][r - 1],dp[i][l][r]);
            if(i + 2 <= n){
              dp[i + 2][l][r] = add(dp[i + 2][l][r],mult(SIGMA - 1,dp[i][l][r]));
            }
          }
          else{
            dp[i + 1][l + 1][r] = add(dp[i + 1][l + 1][r],dp[i][l][r]);
            if(l != r){
              dp[i + 1][l][r - 1] = add(dp[i + 1][l][r - 1],dp[i][l][r]);
            }
            if(i + 2 <= n){
              dp[i + 2][l][r] = add(dp[i + 2][l][r],mult(SIGMA - 1 - (l != r),dp[i][l][r]));
            }
          }
        }else{
            if(i + 2 <= n){
              dp[i + 2][l][r] = add(dp[i + 2][l][r],mult(SIGMA,dp[i][l][r]));
            }
        }
      }
    }
  }

  int ans = 0;

  for(int l = 0;l <= n + 1;l++){
    for(int r = 0;r <= n + 1;r++){
      if(r < l){
        ans = add(ans,dp[n][l][r]);
      }
    }
  }

  printf("%d\n",ans);
  
  return 0;
}
