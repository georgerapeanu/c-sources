#include <cstdio>
#include <algorithm>

using namespace std;

const int NMAX = 1e5;
int n;
int b[NMAX + 5];
int dp[(1 << 15)];

int main(){
	
	scanf("%d",&n);
	
	for(int i = 1;i < n;i++){
		int x,y,z;
		scanf("%d %d %d",&x,&y,&z);
		x++;
		y++;
		b[x] ^= z;
		b[y] ^= z;
	}
	
	int ans = n;
	int mask = 0;
	
	
	for(int i = 1;i <= n;i++){
		if(b[i] == 0){
			ans--;
		}
		else if((mask >> (b[i] - 1)) & 1){
			mask ^= (1 << (b[i] - 1));
			ans--;
		}
		else{
			mask ^= (1 << (b[i] - 1));
		}
	}
		
	dp[0] = 0;
	
	for(int i = 1;i <= mask;i++){
		dp[i] = -(1 << 28);
		for(int j = i;j;j = (j - 1) & i){
			int xo = 0;
			
			for(int b = 0;b < 15;b++){
				if((j >> b) & 1){
					xo ^= (b + 1);///cause i subtracted 1 before to make them in [0,15) range
				}
			}
			
			if(xo == 0){
				dp[i] = max(dp[i],1 + dp[i ^ j]);
			}
		}
	}
	
	ans -= dp[mask];
	
	printf("%d",ans);
	
	return 0;
}