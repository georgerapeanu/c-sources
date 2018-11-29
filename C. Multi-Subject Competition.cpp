#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int n,m;
vector<int> probes[100005];
vector<pair<int,long long> > se_baga[100005];
vector<int> active;

int main(){
	scanf("%d %d",&n,&m);
	
	for(int i = 1;i <= n;i++){
		int s,r;
		scanf("%d %d",&s,&r);		
		probes[s].push_back(r);
	}
	
	for(int i = 1;i <= m;i++){
		sort(probes[i].begin(),probes[i].end());
		reverse(probes[i].begin(),probes[i].end());
		
		long long sum = 0;
		
		for(auto it:probes[i]){
			sum += it;
		}
		
		while(probes[i].size() && sum <= 0){
			sum -= probes[i].back();
			probes[i].pop_back();
		}
		
		
		
		se_baga[probes[i].size()].push_back({i,sum});
	}

	long long tmp = 0;
	long long ans = 0;
	
	for(int i = n;i;i--){
		for(auto it:active){
			tmp -= probes[it].back();
			probes[it].pop_back();
		}
		for(auto it:se_baga[i]){
			tmp += it.second;
			active.push_back(it.first);
		}
		ans = max(ans,tmp);
	}
	
	printf("%I64d ",ans);
	
	return 0;
}