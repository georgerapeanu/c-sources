#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int NMAX = 3e5;
const int MOD = 998244353;
///final code
int n;
vector<int> graph[NMAX + 5];

int dp[NMAX + 5][3];

int lgpow(int b,int e){
	int p = 1;
	while(e){
		if(e & 1){
			p = 1LL * p * b % MOD;
		}
		b = 1LL * b * b % MOD;
		e >>= 1;
	}
	return p;
}

void dfs(int nod,int tata){
	dp[nod][2] = 1;
	dp[nod][0] = 1;
	dp[nod][1] = 0;
	
	int P = 1;
	
	for(auto it:graph[nod]){
		if(it == tata){
			continue;
		}
		dfs(it,nod);
		dp[nod][2] = 1LL * dp[nod][2] * ((long long)dp[it][1] + dp[it][2]) % MOD;
		dp[nod][0] = 1LL * dp[nod][0] * (2LL * dp[it][1] + dp[it][2]) % MOD;
		P = 1LL * P * (2LL * dp[it][1] + dp[it][2]) % MOD;
	}
	
	for(auto it:graph[nod]){
		if(it == tata){
			continue;
		}
		dp[nod][1] = (dp[nod][1] + 1LL * dp[it][0] * ((1LL * P * lgpow((2LL * dp[it][1] + dp[it][2]) % MOD,MOD - 2)) % MOD)) % MOD;
	}
}

int main(){

	scanf("%d",&n);
	
	for(int i = 1;i < n;i++){
		int x,y;
		scanf("%d %d",&x,&y);
		graph[x].push_back(y);
		graph[y].push_back(x);
	}
	
	dfs(1,0);
	
	printf("%d",(dp[1][1] + dp[1][2]) % MOD);
	
	return 0;
}