#include <cstdio>
#include <algorithm>

using namespace std;

const int MOD = 1.e9 + 7;

char s[25][25];
int dp[(1 << 20) + 5];
int sum[25][(1 << 20) + 5];
int n, m;

int main() {
  freopen("karma.in", "r", stdin);
  freopen("karma.ok", "w", stdout);

  scanf("%d%d ", &n, &m);
  for (int i = 1; i <= n; ++i)
    scanf("%s", s[i] + 1);
  int ns = (1 << m);
  dp[0] = 1;
  for (int i = 1; i < ns; ++i) {
    int b;
    for (int j = 0; j < m; ++j) {
      if ((1 << j) & i) {
        b = j;
        break;
      }
    }
    bool valid = 1;
    for (int j = 1; j <= n; ++j) {
      int ad = 1;
      if (s[j][b + 1] == ')')
        ad = -1;
      sum[j][i] = sum[j][i ^ (1 << b)] + ad;
      if (sum[j][i] < 0)
        valid = 0;
    }
    if (valid == 1) {
      for (int j = 0; j < m; ++j)
        if ((1 << j) & i)
          dp[i] = (dp[i] + dp[i ^ (1 << j)]) % MOD;
    }
  }
  printf("%d\n", dp[ns - 1]);

  return 0;
}
