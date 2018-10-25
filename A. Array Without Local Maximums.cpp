#include <cstdio>

using namespace std;

const int MOD = 998244353;
const int NMAX = 1e5;

int add(int a,int b){
	a += b;
	if(a >= MOD){
		a -= MOD;
	}
	return a;
}

int scad(int a,int b){
	a -= b;
	if(a < 0){
		a += MOD;
	}
	return a;
}

int mult(int a,int b){
	return 1LL * a * b % MOD;
}

int n;
int v[NMAX + 5];

int dp[2][205][2];

int main(){

	scanf("%d",&n);
	
	for(int i = 1;i <= n;i++){
		scanf("%d",&v[i]);
	}
	
	dp[0][0][0] = 1;
	dp[0][1][0] = MOD - 1;
	
	for(int i = 0,l = 0;i < n;i++,l ^= 1){
		
	
		for(int j = 1;j <= 200;j++){
			dp[l][j][0] = add(dp[l][j][0],dp[l][j - 1][0]);
			dp[l][j][1] = add(dp[l][j][1],dp[l][j - 1][1]);
		}
		
		if(v[i] != -1){
			for(int j = 1;j <= 200;j++){
				if(j != v[i]){
					dp[l][j][0] = 0;
					dp[l][j][1] = 0;
				}
			}
		}
	
		for(int j = 0;j <= 200;j++){
						
			dp[l ^ 1][j + 1][0] = add(dp[l ^ 1][j + 1][0],dp[l][j][0]);
			
			if(j){
				dp[l ^ 1][j][1] = add(dp[l ^ 1][j][1],dp[l][j][0]);
				dp[l ^ 1][j + 1][1] = scad(dp[l ^ 1][j + 1][1],dp[l][j][0]);
			
				dp[l ^ 1][1][1] = add(dp[l ^ 1][1][1],dp[l][j][1]);
				dp[l ^ 1][j + 1][1] = scad(dp[l ^ 1][j + 1][1],dp[l][j][1]);
			}
			
			dp[l ^ 1][j + 1][0] = add(dp[l ^ 1][j + 1][0],dp[l][j][1]);
			
			dp[l][j][0] = 0;
			dp[l][j][1] = 0;
		}
	}
	
	int ans = 0;
		
	int l = n % 2;
	
	for(int j = 1;j <= 200;j++){
		dp[l][j][0] = add(dp[l][j][0],dp[l][j - 1][0]);
		dp[l][j][1] = add(dp[l][j][1],dp[l][j - 1][1]);
		if(!(v[n] != -1 && j != v[n])){
			ans = add(ans,dp[l][j][1]);
		}
	}
	
	printf("%d",ans);
	
	return 0;
}