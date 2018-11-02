#include <cstdio>
#include <vector>
#include <cstring>
#include <cstdlib>

using namespace std;

const int NMAX = 5e4;
const int KMAX = 100;
const int MOD = 1e9 + 7;

int t;
int n,k;
int dp[NMAX + 1][KMAX + 1][2];
int a[NMAX + 5];
int lim[NMAX + 5];
vector<int> graph[NMAX + 5];

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

int tmp[KMAX + 5];

void dfs(int nod,int tata){
	lim[nod] = a[nod];
	
	if(a[nod] <= k){
		dp[nod][a[nod]][1]++;
	}
	dp[nod][0][0]++;
	
	for(auto it:graph[nod]){
		if(it == tata){
			continue;
		}
		
		dfs(it,nod);
		
		for(int j = 0;j <= lim[it];j++){
			dp[nod][j][0] = add(dp[nod][j][0],dp[it][j][0]);
			dp[nod][j][0] = add(dp[nod][j][0],dp[it][j][1]);
		}
		dp[nod][0][0] = scad(dp[nod][0][0],1);///empty set
		
		for(int j = 0;j <= lim[nod];j++){
			for(int l = 0;l <= lim[it] && j + l <= k;l++){
				tmp[j + l] = add(tmp[j + l],mult(dp[nod][j][1],dp[it][l][1]));
			}
			tmp[j] = add(tmp[j],dp[nod][j][1]);
		}
		
		lim[nod] = min(k,lim[nod] + lim[it]);
		
		for(int j = 0;j <= lim[nod];j++){
			dp[nod][j][1] = tmp[j];
			tmp[j] = 0;
		}
	}
}

int main(){
	
	fscanf(stdin,"%d",&t);
	
	while(t--){
		fscanf(stdin,"%d %d",&n,&k);
	
		for(int i = 1;i <= n;i++){
			fscanf(stdin,"%d",&a[i]);
		}
		
		for(int i = 1;i < n;i++){
			int x,y;
			fscanf(stdin,"%d %d",&x,&y);
			graph[x].push_back(y);
			graph[y].push_back(x);
		}

		dfs(1,0);
		
		if(k == 0){
			dp[1][k][0] = scad(dp[1][k][0],1);
		}

		fprintf(stdout,"%d\n",add(dp[1][k][0],dp[1][k][1]));
		// fprintf(stderr,"%d %d\n",dp[1][1][0],dp[1][1][1]);
		// fprintf(stderr,"%d %d\n",dp[2][1][0],dp[2][1][1]);
		// fprintf(stderr,"%d %d\n",dp[3][1][0],dp[3][1][1]);
		for(int i = 1;i <= n;i++){
			graph[i].clear();
			memset(dp[i],0,sizeof(dp[i]));
			lim[i] = 0;
		}		
	}
	
	
	return 0;
}