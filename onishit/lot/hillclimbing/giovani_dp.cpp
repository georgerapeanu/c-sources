#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = 1e18;

void solve() {
	int n;
  long long k;
	scanf("%d%lld", &n, &k);
	vector <int> a(n + 1, 0);
	for (int i = 1; i <= n ; ++i) 
		scanf("%d", &a[i]);

	vector <vector <vector <ll>>> dp(n + 1, vector <vector <ll>> (n + k + 1, vector <ll> (k + 1, INF)));

	for (int j = 0; j <= k ; ++j) {
		if (a[1] + j <= n)
			dp[1][a[1] + j][j] = 0;
		else break ;
	}
		
	for (int i = 2; i <= n ; ++i) {
		for (int last = 1; last <= n + k ; ++last) for (int k2 = 0; k2 <= k ; ++k2) { 
			if (dp[i - 1][last][k2] == INF) continue ;
			for (int j = 0; j + k2 <= k && a[i] + j <= n ; ++j) {
				dp[i][a[i] + j][k2 + j] = min(dp[i][a[i] + j][k2 + j], dp[i - 1][last][k2] + abs(last - (a[i] + j)));
			}
		}
	}

	ll ans = INF;
	for (int i = 1; i <= n + k ; ++i) for (int j = 0; j <= k ; ++j)
		ans = min(ans, dp[n][i][j]);
	
	printf("%lld\n", ans);
}

int main() {
	int t;
	scanf("%d", &t);
	while (t--) solve();
	
	return 0;
}
