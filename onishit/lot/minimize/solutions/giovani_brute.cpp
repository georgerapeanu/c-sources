#include "minimize.h"
#include <iostream>
#include <vector>

const long long INF = 1e18;

int n, k;
std::vector <int> a;
std::vector <std::vector<long long>> dp;

void initialize(int _n, int _k, std::vector <int> _a) {
  n = _n;
  k = std::min(_k, _n);
  a = std::move(_a);

  dp.resize(n + 1);
  for (auto &v : dp)
    v.resize(k + 1);
}

void modify(int pos, int val) {
  a[pos] = val;
}

long long calculate() {
  fill(dp[0].begin(), dp[0].end(), 0);

  for (int i = 1; i <= n ; ++i) {
    for (int j = 0; j <= i && j <= k ; ++j) {
      if (j == 0)
        dp[i][j] = INF;
      else
        dp[i][j] = dp[i][j - 1];

      if (i > 1)
        dp[i][j] = std::min(dp[i][j], dp[i - 1][j] + (a[i] ^ a[i - 1]));
      else
        dp[i][j] = 0;

      // 'delete l positions in the range [i - l, i - 1]
      for (int l = 1; l <= j && i - l - 1 >= 0 ; ++l) {
        if (i - l - 1 >= 1)
          dp[i][j] = std::min(dp[i][j], dp[i - l - 1][j - l] + (a[i - l - 1] ^ a[i]));
        else
          dp[i][j] = 0;
      }
    }

    for (int j = i - 1; j <= k ; ++j)
      dp[i][j] = 0;
  }

  long long ans = dp[n][k];
  for (int l = 1; l <= k && n - l >= 0 ; ++l)
    ans = std::min(ans, dp[n - l][k - l]);

  return ans;
}
