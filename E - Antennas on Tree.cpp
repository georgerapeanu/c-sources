#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int NMAX = 1e5;

int n;
vector<int> graph[NMAX + 5];

int leafs[NMAX + 5];
int dp[NMAX + 5];

void dfs(int nod,int tata){
	bool have = false;
	
	if(graph[nod].size() == 1 && graph[nod][0] == tata){
		dp[nod] = 1;
		leafs[nod] = 1;
		return;
	}
	
	for(auto it:graph[nod]){
		if(it == tata){
			continue;
		}
		dfs(it,nod);
		leafs[nod] += leafs[it];
		dp[nod] += dp[it];
		have |= (leafs[it] == 1);
	}
	
	dp[nod] -= (have && graph[nod].size() != 1 + (tata != 0));
}

int main(){
	
	scanf("%d",&n);
	
	for(int i = 1;i < n;i++){
		int x,y;
		scanf("%d %d",&x,&y);
		x++;y++;
		graph[x].push_back(y);
		graph[y].push_back(x);
	}

	for(int i = 1;i <= n;i++){
		if(graph[i].size() > 2){
			dfs(i,0);
			printf("%d",dp[i]);
			return 0;
		}
	}
	
	printf("%d",1);
	
	return 0;
}