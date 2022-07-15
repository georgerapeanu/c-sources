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

int invmod(int x) {
  return lgput(x, MOD - 2);
}

int solve(int n, int m) {
  MOD = m;
  
  vector <int> p2(n + 1, 0), ip2(n + 1, 0);
  p2[0] = 1;
  for (int i = 1; i <= n ; ++i)
    p2[i] = p2[i - 1] * 2LL % MOD;

  ip2[n] = invmod(p2[n]);
  for (int i = n - 1; i >= 0 ; --i)
    ip2[i] = ip2[i + 1] * 2LL % MOD;

  // prec(i, j) = the number of expressions of length i with the 
  //              largest term size being j,
  //              not containing the character '=' 
  vector <vector <int>> prec(n + 1, vector <int> (n + 1, 0));
  prec[0][0] = 1;

  for (int i = 0; i <= n ; ++i) {
    for (int j = 0; j <= i ; ++j) {
      for (int l = 1; l <= n ; ++l) {
        int nxt = i + l + 1;
        if (i == 0)
          --nxt;
        if (nxt > n)
          break;
        prec[nxt][max(j, l)] = (prec[nxt][max(j, l)] + 1LL * prec[i][j] * p2[l]) % MOD;
      }
    }
  }

  for (int i = 1; i <= n ; ++i) {
    for (int j = 1; j <= i ; ++j)
      prec[i][j] = 1LL * prec[i][j] * ip2[j] % MOD;
  }

  // dp(i, j) = the number of expressions of length i with the 
  //            smallest term size being j
  vector <vector <int>> dp(n + 1, vector <int> (n + 1, 0));
  dp[0][n] = 1;

  for (int i = 0; i <= n ; ++i) {
    for (int j = 0; j <= n ; ++j) {
      if (dp[i][j] == 0)
        continue;

      for (int k = 1; k + i <= n ; ++k) {
        for (int len = k; len <= n; ++len) {
          int nxt = i + len + 1;
          if (i == 0) {
            --nxt;
            if (nxt == n)
              break;
          }
          if (nxt > n)
            break;
          dp[nxt][min(j, k)] = (dp[nxt][min(j, k)] + 1LL * dp[i][j] * prec[len][k]) % MOD;
        }
      }
    }
  }

  int ans = 0;
  for (int j = 0; j < n ; ++j)
    ans = (ans + 1LL * dp[n][j] * p2[j]) % MOD;

  return ans;
}
