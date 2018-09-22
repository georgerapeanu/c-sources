#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

FILE *f=fopen("oxificare.in","r");
FILE *g=fopen("oxificare.out","w");

const int NMAX = 1e3;
const int LMAX = 1e4;

int t,n;
int cost[NMAX + 5];
int father[NMAX + 5];

vector<int> graph[NMAX + 5];
int dp[NMAX + 5][LMAX + 5];

int main(){
	
	fscanf(f,"%d",&t);
	while(t--){
		fscanf(f,"%d",&n);
		
		for(int i = 1;i <= n;i++){
			graph[i].clear();
			for(int j = 0;j <= LMAX;j++){
				dp[i][j] = 1 << 30;
			}
		}
		
		dp[1][0] = 0;
		
		for(int i = 2;i <= n;i++){
			fscanf(f,"%d",&father[i]);
			graph[father[i]].push_back(i);
		}
		
		for(int i = 2;i <= n;i++){
			fscanf(f,"%d",&cost[i]);
		}
		
		for(int i = n;i >= 1;i--){
			if(graph[i].size() == 0){
				dp[i][0] = 0;
			}
			
			for(int j = 0;j <= LMAX;j++){
				for(auto it:graph[i]){
					int tmp = 1 << 30;
					if(j + cost[it] <= LMAX){
						if(dp[it][j + cost[it]] != 1 << 30){
							tmp = min(tmp,dp[it][j + cost[it]] + cost[it]);
						}
					}
					
					if(j - cost[it] >= 0){
						if(dp[it][j - cost[it]] != 1 << 30){
							tmp = min(tmp,max(dp[it][j - cost[it]] - cost[it],0));
						}
					}
					dp[i][j] = max(dp[i][j] == 1 << 30 ? -1:dp[i][j],tmp);
				}
				
				if(j){				
					dp[i][j] = min(dp[i][j - 1],dp[i][j]);
				}
			}	
		}

		int ans = 1 << 30;
		
		for(int j = 0;j <= LMAX;j++){
			if(dp[1][j] == 1 << 30){
				continue;
			}
			ans = min(ans,dp[1][j] + j);
		}
		
		fprintf(g,"%d\n",ans);
	}
	
    fclose(f);
    fclose(g);
    return 0;
}