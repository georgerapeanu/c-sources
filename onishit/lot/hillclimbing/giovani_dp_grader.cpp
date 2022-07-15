#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = 1e18;

long long solve(int n, long long k, int V[]) {
	vector <int> a(n + 1, 0);
  int vmax = 0;
	for (int i = 1; i <= n ; ++i) {
    a[i] = V[i - 1];
    vmax = max(vmax, a[i]);
  }

	vector <vector <vector <ll>>> dp(n + 1, vector <vector <ll>> (vmax + k + 1, vector <ll> (k + 1, INF)));

	for (int j = 0; j <= k ; ++j) {
		if (a[1] + j <= vmax)
			dp[1][a[1] + j][j] = 0;
		else break ;
	}
		
	for (int i = 2; i <= n ; ++i) {
		for (int last = 1; last <= vmax + k ; ++last) for (int k2 = 0; k2 <= k ; ++k2) { 
			if (dp[i - 1][last][k2] == INF) continue ;
			for (int j = 0; j + k2 <= k && a[i] + j <= vmax ; ++j) {
				dp[i][a[i] + j][k2 + j] = min(dp[i][a[i] + j][k2 + j], dp[i - 1][last][k2] + abs(last - (a[i] + j)));
			}
		}
	}

	ll ans = INF;
	for (int i = 1; i <= vmax ; ++i) for (int j = 0; j <= k ; ++j)
		ans = min(ans, dp[n][i][j]);
	
  return ans;
}
