#include <bits/stdc++.h>
#include "ghinion.h"

using namespace std;

int MOD;

int lgput(int x, int p) {
  int aux = x, ans = 1;  

  for (int i = 1; i <= p ; i = i << 1) {
    if (i & p)
      ans = 1LL * ans * aux % MOD;
    aux = 1LL * aux * aux % MOD;
  }

  return ans;
}

int solve(int n, int m) {
  MOD = m;
  
  vector <int> p2(n + 1, 0);
  p2[0] = 1;
  for (int i = 1; i <= n ; ++i)
    p2[i] = p2[i - 1] * 2LL % MOD;

  // prec(i, j) = the number of expressions of length i with the 
  //              largest term size being j,
  //              not containing the character '='
  vector <vector <int>> prec(n + 1, vector <int> (n + 1, 0));

  for (int i = 1; i < n ; ++i) {
    prec[i][i] = 1;
    for (int j = 1; j <= i ; ++j) {
      for (int l = 1; i + l + 1 <= n ; ++l) {
        int nxt = i + l + 1;
        prec[nxt][max(j, l)] = (prec[nxt][max(j, l)] + 1LL * prec[i][j] * p2[min(j, l)]) % MOD;
      }
    }
  }

  for (int i = 1; i <= n ; ++i) {
    for (int j = i - 1; j >= 1 ; --j) {
      prec[i][j] = (1LL * prec[i][j] + prec[i][j + 1]) % MOD;
    }
  }

  // dp(i, j) = the number of expressions of length i with the
  //            smallest term size being j
  vector <vector <int>> dp(n + 1, vector <int> (n + 1, 0));

  for (int i = 1; i < n ; ++i) {
    for (int j = 1; j <= i ; ++j) {
      dp[i][j] = (1LL * dp[i][j] + prec[i][j]) % MOD;
      for (int k = 1; i + 1 + k <= n ; ++k) {
        dp[i + 1 + k][j] = (dp[i + 1 + k][j] + 1LL * prec[k][j] * dp[i][j]) % MOD;
      }
    }
  }

  int ans = 0;
  for (int j = n; j >= 1 ; --j) {
    for (int k = j + 1; k <= n ; ++k)
      dp[n][j] = (1LL * dp[n][j] - dp[n][k] + MOD) % MOD;
    ans = (ans + 1LL * dp[n][j] * p2[j]) % MOD;
  }
  return ans;
}

