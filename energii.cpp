#include <cstdio>
#include <algorithm>

using namespace std;

FILE *f = fopen("energii.in","r");
FILE *g = fopen("energii.out","w");

int G,W;
int Cost[10001];
int En[10001];
int dp[2][10001];

int main(){
	
	fscanf(f,"%d %d",&G,&W);
	
	for(int i = 1;i <= G;i++){
		fscanf(f,"%d %d",&En[i],&Cost[i]);
	}
	
	for(int i = 0;i <= 1;i++){
		for(int j = 0;j <= 10000;j++){
			dp[i][j] = 1 << 30;
		}
	}
	
	dp[0][0] = 0;
	
	for(int i = 1;i <= G;i++){
		for(int j = 0;j <= 10000;j++){
			dp[i & 1][j] = dp[1 - (i & 1)][j];
			if(j >= En[i]){
				dp[i & 1][j] = min(dp[i & 1][j],dp[1 - (i & 1)][j - En[i]] + Cost[i]);
			}
		}
	}
	
	int ans = 1 << 30;
	
	for(int j = W;j <= 10000;j++){
		ans = min(ans,dp[G & 1][j]);
	}
	
	fprintf(g,"%d",ans == 1 << 30 ? -1:ans);
	
	fclose(f);
	fclose(g);

	return 0;
}