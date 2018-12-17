#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int n;
int p[2005];
int a[2005];
int lvl[2005];
int wh[2005];
int leafish_factor[2005];
bool active[2005];
int cnt_active;

vector<int> moves;

void move(int node){
	moves.push_back(node);
	vector<int> tmp;
	
	while(node){
		tmp.push_back(node);
		node = p[node];
	}
	
	tmp.push_back(0);
	
	reverse(tmp.begin(),tmp.end());
	for(int i = 0;i < (int)tmp.size() - 1;i++){
		swap(wh[a[tmp[i]]],wh[a[tmp[i + 1]]]);
		swap(a[tmp[i]],a[tmp[i + 1]]);
	}
}

int main(){
	
	scanf("%d",&n);
	
	for(int i = 1;i < n;i++){
		scanf("%d",&p[i]);
		lvl[i] = 1 + lvl[p[i]];
	}
	
	for(int i = 0;i < n;i++){
		scanf("%d",&a[i]);
		wh[a[i]] = i;
		active[i] = true;
		cnt_active++;
	}
	
	while(cnt_active > 0){
		for(int i = 0;i < n;i++){
			leafish_factor[i] = 0;
		}
		
		for(int i = n - 1;i >= 0;i--){
			if(!active[i]){
				continue;
			}
			leafish_factor[i] = max(leafish_factor[i],1);
			if(i){
				leafish_factor[p[i]] += leafish_factor[i];
			}
		}
		
		vector< vector<int> > batch;
		vector< vector<int> > c_batch;
		vector< vector<bool> > inserted;
		for(int i = n - 1;i >= 0;i--){
			if(active[i] && leafish_factor[i] == 1){
				int nod = i;
				vector<int> path;
				while(leafish_factor[nod] == 1 && nod){
					path.push_back(nod);
					active[nod] = false;
					cnt_active--;
					nod = p[nod];
				}
				if(nod == 0 && leafish_factor[nod] == 1){
					cnt_active--;
					active[0] = false;
					path.push_back(0);
				}
				batch.push_back(path);
				inserted.push_back(vector<bool>(path.size(),false));
			}
		}
		c_batch = batch;
		
		while(1){
			for(auto it:batch){
				break_cond &= it.empty();
			}
			if(break_cond){
				break;
			}
			
			bool found = false;
			
			for(int i = 0;!found && i < (int)c_batch.size();i++){
				int ins = 0;
				for(int j = 0;j < (int)c_batch[i].size();j++){
					ins += inserted[i][j];///inserted lower than you
					if(a[0] == c_batch[i][j]){
						inserted[i][j] = true;
						move(c_batch[i][ins]);
						for(int k = 0;k < (int)batch[i].size();k++){
							if(batch[i][k] == c_batch[i][j]){
								swap(batch[i][k],batch[i].back());
								break;
							}
						}
						batch[i].pop_back();
						found = true;
						break;
					}
				}
			}
			
			if(!found){
				int node = 0;
				for(auto it:batch){
					for(auto it2:it){
						node = (lvl[wh[it2]] > lvl[node] ? wh[it2]:node);
					}
				}
				move(node);
			}
		}
		
	}
	
	printf("%d\n",moves.size());
	
	for(auto it:moves){
		printf("%d\n",it);
	}
	
	return 0;
}