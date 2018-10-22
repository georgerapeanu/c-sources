#include <cstdio>
#include <algorithm>

using namespace std;

FILE *f = fopen("piruete.in","r");
FILE *g = fopen("piruete.out","w");

const int MOD = 1e9 + 7;

int t,n,k;

int dp[2][105][105][105];
int delta[2][105][105][105];

void add(int &a,int b){
	a += b;
	if(a >= MOD){
		a -= MOD;
	}
}

int main(){

	fscanf(f,"%d %d %d",&t,&n,&k);
	
	t /= 2;
	
	dp[0][0][0][0] = 1;
	
	for(int i = 0,l = 0;i <= k;i++,l ^= 1){

		for(int j = min((long long)t,1LL * (i / 2) * (i / 2 + 1));j <= t;j++){
			for(int x = min(n + 1,i / 2);x <= n + 1;x++){
				for(int y = min(n + 1,i / 2);y <= n + 1;y++){
					if(j && y && y != n + 1){
						add(delta[l][j][x][y],delta[l][j - 1][x][y - 1]);
					}

					add(dp[l][j][x][y],delta[l][j][x][y]);
					
					if(dp[l][j][x][y] == 0){
						continue;
					}
					
					if(j == t){
						for(int o = x + 1;o <= n;o++){
							add(dp[l ^ 1][j][y][o],dp[l][j][x][y]);
						}
						
						for(int o = y + 1;o <= n;o++){
							add(dp[l ^ 1][j][n + 1][o],dp[l][j][x][y]);
						}
					}
					
					else{
						if(j + n + 1 <= t){
							add(dp[l][j + n + 1][y][n + 1],dp[l][j][x][y]);
						}
						
						if(x + 1 <= n && j + x + 1 <= t){
							add(delta[l ^ 1][j + x + 1][y][x + 1],dp[l][j][x][y]);
						}
					}
				}
			}
		}
		
		for(int j = min((long long)t,1LL * (i / 2) * (i / 2 + 1));j <= t;j++){
			for(int x = min(n + 1,i / 2);x <= n + 1;x++){
				for(int y = min(n + 1,i / 2);y <= n + 1;y++){
					if(i != k){
						dp[l][j][x][y] = 0;
						delta[l][j][x][y] = 0;
					}
				}
			}
		}
		
	}
	
	int ans = 0;
	
	for(int x = 0;x <= n + 1;x++){
		for(int y = 0;y <= n + 1;y++){
			add(ans,dp[k % 2][t][x][y]);
		}
	}
	
	fprintf(g,"%d",ans);

	fclose(f);
	fclose(g);
	
	return 0;
}