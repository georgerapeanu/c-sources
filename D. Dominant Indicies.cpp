#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int N;

vector<int> G[1000005];

int W[1000005];
int big[1000005];
int ans[1000005];
int father[1000005];
int lvl[1000005];

void pre_dfs(int nod,int tata){
	father[nod] = tata;
	W[nod] = 1;
	for(auto it:G[nod]){
		if(it == tata){
			continue;
		}
		pre_dfs(it,nod);
		W[nod] += W[it];
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

vector<int> D;
vector<int> pref_max;
int dominant_ind;

void dfs(int nod,bool dump){
	for(auto it:G[nod]){
		if(it != father[nod] && it != big[nod]){
			dfs(it,1);
		}
	}
	
	dfs(big[nod],0);
	
	D.push_back(1);
	pref_max.push_back(pref_max.size() > 0 ? pref_max.back() : 1);
	
	for(auto it:G[nod]){
		if(it != father[nod] && it != big[nod]){
			vector<int> V = subtree(it);
			for(auto it:V){
				D[(int)D.size() - 1 + lvl[nod] - lvl[it]]++;
				if((int)D.size() - 1 + lvl[nod] - lvl[it] > dominant_ind){
					if(D[(int)D.size() - 1 + lvl[nod] - lvl[it]] >= D[dominant_ind]){
						dominant_ind = 0;
					}
				}
				else{
					if(D[(int)D.size() - 1 + lvl[nod] - lvl[it]] > D[dominant_ind]){
							dominant_ind = 0;
						}
				}
			}
			
			reverse(V.begin(),V.end());
			
			for(auto it:V){
				pref_max[(int)D.size() - 1 + lvl[nod] - lvl[it]] = (((int)D.size() - 1 + lvl[nod] - lvl[it] == 0 ? 0 : pref_max[(int)D.size() - 1 + lvl[nod] - lvl[it] - 1]),D[(int)D.size() - 1 + lvl[nod] - lvl[it]]); 
			}
			
			if(D.size() > 1){
				pref_max[D.size() - 1] = max(pref_max[D.size() - 1],pref_max[D.size() - 2]);
			}
			
			int suf_max = 1;
			
			for(auto it:V){
				if(suf_max < D[(int)D.size() - 1 + lvl[nod] - lvl[it]] && D[(int)D.size() - 1 + lvl[nod] - lvl[it]] >= ((int)D.size() - 1 + lvl[nod] - lvl[it] == 0 ? 0 : pref_max[(int)D.size() - 1 + lvl[nod] - lvl[it] - 1])){
					dominant_ind = (int)D.size() - 1 + lvl[nod] - lvl[it];
				}
				suf_max = max(suf_max,D[(int)D.size() - 1 + lvl[nod] - lvl[it]]);
			}
			
		}
	}
	
	ans[nod] = lvl[nod] + ((int)D.size() - 1) - dominant_ind;
	
	if(dump){
		dominant_ind = 0;
		D.clear();
		pref_max.clear();
	}
}

int main(){
	
	
	return 0;
}