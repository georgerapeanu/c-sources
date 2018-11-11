#include <cstdio>
#include <cstring>
#include <algorithm>
 
using namespace std;
 
FILE *f = fopen("stiva.in","r");
FILE *g = fopen("stiva.out","w");
 
int n;
char c[505];
int dp[505][505];
 
int main(){
 
	fgets(c + 1,505,f);
	
	n = strlen(c + 1);
	n -= (c[n] == '\n');
 
	for(int i = 1;i <= n;i++){
		dp[i][i] = 1;
	}
 
	for(int l = 1;l < n;l++){
		for(int i = 1;i <= n - l;i++){
			int j = i + l;
			dp[i][j] = dp[i][j - 1] + 1;
 
			if(c[i] == c[j]){
				dp[i][j] = min(dp[i][j],dp[i][j - 1]);
			}		
			
			for(int k = i;k < j;k++){
				dp[i][j] = min(dp[i][j],dp[i][k] + dp[k + 1][j]);
			}
		}
	}
 
	fprintf(g,"%d\n",2 * dp[1][n] + n);
 
	fclose(f);
	fclose(g);
 
	return 0;
}