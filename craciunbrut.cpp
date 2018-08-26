#include <bits/stdc++.h>
 
using namespace std;
 
long long dp[3005][3005];
int c[3005];
 
vector<int>G[3005];
 
int n1;
 
void dfs(int n) {
  for (auto it:G[n])
    dfs(it);
  for (int i = 1; i <= n1; ++i) {
    dp[n][i] = c[n];
    for (auto it:G[n])
      dp[n][i] += dp[it][i - 1];
  }
}
 
int main() {
  freopen("craciun.in", "r", stdin);
  freopen("craciun.ok", "w", stdout);
 
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &c[i]);
  for (int i = 2; i <= n; ++i) {
    int x;
    scanf("%d", &x);
    G[x].push_back(i);
  }
 
  n1 = n;
  dfs(1);
 
  double ans = 0;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      ans = max(ans, (double)dp[i][j] / j);
  printf("%.4f\n", ans);
 
  return 0;
}