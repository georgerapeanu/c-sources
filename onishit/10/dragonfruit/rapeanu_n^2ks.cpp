#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2000;
const int KMAX = 1000;
const int SMAX = 15;
const int inf = 1e9;

const int MOD = 1e9 + 7;

ifstream f("dragonfruit.in");
ofstream g("dragonfruit.out");

int add(int a, int b){
  a += b;
  if(a >= MOD){
    a -= MOD;
  }
  return a;
}

int scad(int a, int b){
  a -= b;
  if(a < 0){
    a += MOD;
  }
  return a;
}

int mult(int a, int b){
  return 1LL * a * b % MOD;
}


int t;
int n, k, s;
int dp[2][NMAX + 1][KMAX + 1];
int cnt_dp[2][NMAX + 1][KMAX + 1];
int v[NMAX + 5];

int main(){
  
  f >> t;

  while(t--){
    f >> n >> k >> s;

    for(int i = 1;i <= n;i++){
      f >> v[i];
    }
    
    for(int i = 0;i <= n;i++){
      for(int j = 0;j <= k;j++){
        dp[0][i][j] = dp[1][i][j] = inf;
        cnt_dp[0][i][j] = cnt_dp[1][i][j] = 0;
      }
    }

    for(int i = 0;i <= n;i++){
      dp[0][i][0] = 0;
      cnt_dp[0][i][0] = 1;
    }

    pair<int, int> ans = {inf, 0};

    for(int h = 1;h <= s;h++){
      for(int i = 0; i <= n;i++){
        for(int j = 0;j <= k;j++){
          dp[h & 1][i][j] = inf;
          cnt_dp[h & 1][i][j] = 0;
          int sum = 0;
          for(int l = i - 1;l >= 0;l--){
            sum += v[l + 1];
            if(sum > j){
              break;
            }
            if(dp[1 - (h & 1)][l][j - sum] + (i - l) < dp[h & 1][i][j]){
              dp[h & 1][i][j] = dp[1 - (h & 1)][l][j - sum] + i - l;
              cnt_dp[h & 1][i][j] = cnt_dp[1 - (h & 1)][l][j - sum];
            }else if(dp[1 - (h & 1)][l][j - sum] + (i - l) == dp[h & 1][i][j]){
              cnt_dp[h & 1][i][j] = add(cnt_dp[h & 1][i][j], cnt_dp[1 - (h & 1)][l][j - sum]);
            }
          }

          if(i > 0){
            if(dp[h & 1][i][j] > dp[h & 1][i - 1][j]){
              dp[h & 1][i][j] = dp[h & 1][i - 1][j];
              cnt_dp[h & 1][i][j] = cnt_dp[h & 1][i - 1][j];
            }else if(dp[h & 1][i][j] == dp[h & 1][i - 1][j]){
              cnt_dp[h & 1][i][j] = add(cnt_dp[h & 1][i][j], cnt_dp[h & 1][i - 1][j]);
            }
          }
        }
      }
      if(ans.first > dp[h & 1][n][k]){
        ans.first = dp[h & 1][n][k];
        ans.second = cnt_dp[h & 1][n][k];
      }else if(ans.first == dp[h & 1][n][k]){
        ans.second = add(cnt_dp[h & 1][n][k], ans.second);
      }
    }
    if(ans.first == inf){
      ans = {0, 0};
    }
    g << ans.first << " " << ans.second << "\n";
  }

  f.close();
  g.close();

  return 0;

}
