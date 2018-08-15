#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>

using namespace std;

int N;

vector<int> G[1000005];

int W[1000005];
int big[1000005];
int ans[1000005];
int father[1000005];
int lvl[1000005];
int max_depth[1000005];

void pre_dfs(int nod,int tata){
	lvl[nod] = 1 + lvl[tata];
	father[nod] = tata;
	W[nod] = 1;
	max_depth[nod] = lvl[nod];

	for(auto it:G[nod]){
		if(it == tata){
			continue;
		}
		pre_dfs(it,nod);
		W[nod] += W[it];
		max_depth[nod] = max(max_depth[it],max_depth[nod]);
		if(W[big[nod]] < W[it]){
			big[nod] = it;
		}
	}
}

vector<int> subtree(int nod){
	vector<int> ans;
	ans.push_back(nod);
	for(auto it:ans){
		for(auto it2:G[it]){
			if(it2 != father[it]){
				ans.push_back(it2);
			}
		}
	}
	return ans;
}

vector<int> dist_cnt;
int dominant_ind;

void dfs(int nod,bool dump){

	for(auto it:G[nod]){
		if(it != father[nod] && it != big[nod]){
			dfs(it,1);
		}
	}

	if(big[nod]){
		dfs(big[nod],0);
	}
	
	dist_cnt[lvl[nod]]++;

	if(lvl[nod] == max_depth[nod] || (1 > dist_cnt[dominant_ind] || (1 == dist_cnt[dominant_ind] && lvl[nod] < dominant_ind))){
		dominant_ind = lvl[nod];
	}

	for(auto it:G[nod]){
        if(it != father[nod] && it != big[nod]){
            vector<int> nodes = subtree(it);

            for(auto it2:nodes){
                dist_cnt[lvl[it2]]++;
				if((dist_cnt[lvl[it2]] > dist_cnt[dominant_ind] || (dist_cnt[lvl[it2]] == dist_cnt[dominant_ind] && lvl[it2] < dominant_ind))){
					dominant_ind = lvl[it2];
				}
            }
        }
	}

	ans[nod] = dominant_ind - lvl[nod];
	
	if(dump){
		for(int height = lvl[nod]; height <= max_depth[nod]; height++){
			dist_cnt[height] = 0;
		}
		dominant_ind = 0;
	}
}

int main(){

	scanf("%d",&N);

	for(int i = 1;i < N;i++){
		int x,y;
		scanf("%d %d",&x,&y);
		G[x].push_back(y);
		G[y].push_back(x);
	}

	dist_cnt.resize(N + 2,0);

	pre_dfs(1,0);
	dfs(1,1);

	for(int i = 1;i <= N;i++){
		printf("%d\n",ans[i]);
	}

	return 0;
}
