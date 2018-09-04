#include <vector>
#include <set>
#include <iostream>

using namespace std;

const int NMAX = 2e5;
int n,m,k;
vector<int> graph[NMAX + 5];
set< pair<int,int> > nodes;
int x[NMAX + 5];
int y[NMAX + 5];
int gr[NMAX + 5];
int ans[NMAX + 5];
bool active[NMAX + 5];

int main(){
	
	cin >> n >> m >> k;
	
	for(int i = 1;i <= m;i++){
		cin >> x[i] >> y[i];
		graph[x[i]].push_back(y[i]);
		graph[y[i]].push_back(x[i]);
		gr[x[i]]++;
		gr[y[i]]++;
	}
	
	for(int i = 1;i <= n;i++){
		nodes.insert({gr[i],i});
		active[i] = 1;
	}

	for(int i = m;i;i--){
		while(nodes.size() && nodes.begin()->first < k){
			int nod = nodes.begin()->second;
			active[nod] = 0;
			nodes.erase(nodes.begin());
		
			for(auto it:graph[nod]){
				if(!active[it]){
					continue;
				}
				nodes.erase(nodes.find({gr[it],it}));
				gr[it]--;
				nodes.insert({gr[it],it});
			}
		}
		
		ans[i] = nodes.size();
		
		if(active[x[i]]){
			nodes.erase({gr[x[i]],x[i]});
			gr[x[i]] -= active[y[i]];
			nodes.insert({gr[x[i]],x[i]});
		}
		
		if(active[y[i]]){
			nodes.erase({gr[y[i]],y[i]});
			gr[y[i]] -= active[x[i]];
			nodes.insert({gr[y[i]],y[i]});
		
		}
		
		graph[x[i]].pop_back();
		graph[y[i]].pop_back();
		
	}
	
	for(int i = 1;i <= m;i++){
		cout << ans[i] << "\n";
	}
	
	return 0;
}