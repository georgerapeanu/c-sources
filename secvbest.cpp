#include <cstdio>
#include <deque>
#include <algorithm>

using namespace std;

FILE *f = fopen("secvbest.in","r");
FILE *g = fopen("secvbest.out","w");

const int NMAX = 1e5;
const long long inf = 6e15;

int n,k;
long long s;
long long sp[NMAX + 5];

deque<pair<long long,int> > d;

int lim;

long long dp[2][NMAX + 5];

int main(){
	
	fscanf(f,"%d %d %lld",&n,&k,&s);
	
	for(int i = 1;i <= n;i++){
		fscanf(f,"%lld",&sp[i]);
		sp[i] += sp[i - 1];
	}
	
	for(int i = 1;i <= n;i++){
		dp[0][i] = inf;
	}
	
	for(int i = 1,l = 1;i <= k;i++,l ^= 1){
		long long best = inf;
		int ind = -1;
		d.clear();
		
		for(int j = 0;j <= n;j++){
			dp[l][j] = inf;
			
			while(ind < j && sp[j] - sp[ind + 1] > s){
				ind++;
				best = min(best,-sp[ind] - s + dp[1 - l][ind]);
			}
			
			while(!d.empty() && d.front().second <= ind){
				d.pop_front();
			}
			
			dp[l][j] = min(dp[l][j],best + sp[j]);
			
			if(!d.empty()){
				dp[l][j] = min(dp[l][j],-sp[j] + d.front().first);
			}
			
			while(!d.empty() && d.back().first >= s + sp[j] + dp[1 - l][j]){
				d.pop_back();
			}
			
			d.push_back({s + sp[j] + dp[1 - l][j],j});
		}
		
		fprintf(g,"%lld ",dp[l][n]);
	}
	
	
	fclose(f);
	fclose(g);
	
	return 0;
}