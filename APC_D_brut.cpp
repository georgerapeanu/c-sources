#include <cstdio>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;
 	
int MOD, Q;
deque<pair<int,int>> stuff;

void add(int w,int v){
	stuff.push_back({w,v});
}

void rem(){
	stuff.pop_front();
}

long long fi(int l,int r){
	vector<long long> dp[2];
	dp[0] = vector<long long>(MOD,-(1LL << 60));
	dp[1] = vector<long long>(MOD,-(1LL << 60));
	dp[0][0] = 0;
	
	
	for(int i = 0,l = 0;i < (int)stuff.size();i++,l ^= 1){
		for(int j = 0;j < MOD;j++){
			dp[l ^ 1][(j + stuff[i].first) % MOD] = max(dp[l ^ 1][(j + stuff[i].first) % MOD],dp[l][j] + stuff[i].second);
			dp[l ^ 1][j] = max(dp[l ^ 1][j],dp[l][j]);
		}
	}
	
	long long ans = -(1LL << 60);
	
	for(int i = l;i <= r;i++){
		ans = max(ans,dp[(int)stuff.size() & 1][i]);
	}
	
	return (ans < 0 ? -1:ans);
}

int main() {
	
	freopen("in","r",stdin);
	freopen("ok","w",stdout);

	scanf("%d %d", &MOD, &Q);

	for (int i = 0; i < Q; i++) {
		int t, w, v, l, r;
		scanf("%d %d %d %d %d", &t, &w, &v, &l, &r);

		if (t == 1) {
			add(w,v);
		} 
		
		else {
			rem();
		}
		
		
		long long ans = fi(l,r);
		printf("%lld\n", ans);
	}
	
	return 0;
}
