#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

FILE * f = fopen("shuffle2.in","r");
FILE * g = fopen("shuffle2.out","w");

const int MOD = 1e9 + 7;
const int NMAX = 1e5;
const int MMAX = 2e5;

int n,m;

int dp[NMAX + 5];
int min_dist[NMAX + 5];

vector<int> graph[NMAX + 5];
vector<int> transposed_graph[NMAX + 5];

vector<int> topo;

int gr[NMAX + 5];
int base_gr[NMAX + 5];

int fact[MMAX + 5];
int ifact[MMAX + 5];

int lgpow(int b,int e){
	int p = 1;
	
	while(e){
		if(e & 1){
			p = 1LL * b * p % MOD;
		}
		
		b = 1LL * b * b % MOD;
		e >>= 1;
	}
	
	return p;
}

int main(){
	fscanf(f,"%d %d",&n,&m);
	
	fact[0] = 1;
	
	for(int i = 1;i <= m;i++){
		fact[i] = 1LL * i * fact[i - 1] % MOD;
	}
	
	ifact[m] = lgpow(fact[m],MOD - 2);
	
	for(int i = m - 1;i >= 0;i--){
		ifact[i] = 1LL * (i + 1) * ifact[i + 1] % MOD;
	}

	
	for(int i = 1;i <= m;i++){
		int x,y;
		fscanf(f,"%d %d",&x,&y);
		graph[x].push_back(y);
		transposed_graph[y].push_back(x);
		gr[y]++;
		base_gr[x]++;
	}
	
	topo.push_back(1);
	
	dp[1] = fact[m];

	
	for(int i = 0;i < (int)topo.size();i++){
		for(auto it:graph[topo[i]]){
			gr[it]--;
			
			if(!gr[it]){
				topo.push_back(it);
			}
		}
		
		min_dist[topo[i]] = (topo[i] != 1) << 28;
		
		for(auto it:transposed_graph[topo[i]]){
			min_dist[topo[i]] = min(min_dist[topo[i]],min_dist[it] + 1);
		}
		
		for(auto it:transposed_graph[topo[i]]){
			if(min_dist[it] + 1 == min_dist[topo[i]]){
				dp[topo[i]] = (dp[topo[i]] + (1LL * dp[it] * (1LL * ifact[base_gr[it]] * fact[base_gr[it] - 1] % MOD) % MOD)) % MOD;
			}
		}
	}

	fprintf(g,"%d",dp[n]);
	
	fclose(f);
	fclose(g);

	return 0;
}