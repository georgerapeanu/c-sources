#include <bits/stdc++.h>

using namespace std;

const int NMAX = 200;
const int MOD = 98999;
int dp[NMAX + 5][NMAX + 5];
int dp2[NMAX + 5][NMAX + 5];

ifstream f("stirling.in");
ofstream g("stirling.out");

int main(){
  dp[1][1] = 1;
  for(int i = 2;i <= NMAX;i++){
    for(int j = 0;j <= i;j++){
      if(j > 0){
        dp[i][j] = (dp[i - 1][j - 1] + (1 - i) * dp[i - 1][j]) % MOD;
      } else{
        dp[i][j] = ((1 - i) * dp[i - 1][j]) % MOD;
      }
    }
  }
  
  dp2[0][0] = 1;
  for(int i = 1;i <= NMAX;i++){
    for(int j = 1;j <= i;j++){
      dp2[i][j] = (dp2[i - 1][j - 1] + dp2[i - 1][j] * j) % MOD;
    }
  }
  
  int t;
  f >> t;

  while(t--){
    int x, n, m;
    f >> x >> n >> m;
    if(x == 1){
      g << dp[n][m] << "\n";
    } else {
      g << dp2[n][m] << "\n";
    }
  }

  f.close();
  g.close();

  return 0;
}
