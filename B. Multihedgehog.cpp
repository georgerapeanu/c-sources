#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

const int NMAX = 1e5;

int n,k;
vector<int> graph[NMAX + 5];
int link[NMAX + 5];

pair<int,int> dfs(int nod,int tata){
	pair<int,int> ans = {nod,0};
	link[nod] = 0;
	for(auto it:graph[nod]){
		if(it == tata){
			continue;
		}
		pair<int,int> tmp = dfs(it,nod);
		tmp.second++;
		if(tmp.second > ans.second){
			ans = tmp;
			link[nod] = it;
		}
	}
	return ans;
}

int fz_lvl = -1;

void dfs2(int nod,int tata,int lvl){
	if((int)graph[nod].size() - (tata != 0) == 2 || graph[nod].size() == 2){
		printf("No");
		exit(0);
	}
	
	for(auto it:graph[nod]){
		if(it == tata){
			continue;
		}
		dfs2(it,nod,lvl + 1);
	}
	
	if(graph[nod].size() == 1){
		if(fz_lvl != lvl){
			printf("No");
			exit(0);
		}
	}
}

int main(){
	
	scanf("%d %d",&n,&k);
	
	for(int i = 1;i < n;i++){
		int x,y;
		scanf("%d %d",&x,&y);
		graph[x].push_back(y);
		graph[y].push_back(x);
	}
		
	pair<int,int> fst = dfs(1,0);
	pair<int,int> snd = dfs(fst.first,0);
	
	if(snd.second != 2 * k){
		printf("No");
		return 0;
	}
	
	vector<int> diam;
	
	for(int nod = fst.first;nod;nod = link[nod]){
		diam.push_back(nod);
	}		
	
	if(diam.size() % 2 == 0){
		printf("No");
		return 0;
	}
	
	fz_lvl = k + 1;
	
	dfs2(diam[(int)diam.size() / 2],0,1);
	
	printf("Yes");
	
	return 0;
}