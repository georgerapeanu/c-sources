#include <cstdio>
#include <stdexcept>
#include <algorithm>
#include <vector>

using namespace std;

FILE *f = fopen("heavypath.in","r");
FILE *g = fopen("heavypath.out","w");

class SegmentTree{
private:

	bool enforce_throws;
	int n;
	vector<int> aint;
	vector<int> lazy;
	
	void build(int nod,int st,int dr,vector<int> &base){
		lazy[nod] = 0;
		aint[nod] = 0;
		
		if(st == dr){
			aint[nod] = base[st];
			return;
		}
		
		int mid = (st + dr) / 2;
		
		build(nod * 2,st,mid,base);
		build(nod * 2 + 1,mid + 1,dr,base);
		aint[nod] = max(aint[2 * nod],aint[2 * nod + 1]);
	}
	
	void propag(int nod,int st,int dr){
		if(st == dr || !lazy[nod]){
			return;
		}
		
		lazy[2 * nod] += lazy[nod];
		lazy[2 * nod + 1] += lazy[nod];
		aint[2 * nod] += lazy[nod];
		aint[2 * nod + 1] += lazy[nod];
		lazy[nod] = 0;
	}
	
	void update(int nod,int st,int dr,int S,int D,int val){
		propag(nod,st,dr);
		
		if(D < st || S > dr){
			return ;
		}
		
		if(S <= st && dr <= D){
			lazy[nod] += val;
			aint[nod] += val;
			return ;
		}
		
		int mid = (st + dr) / 2;
		
		update(nod * 2,st,mid,S,D,val);
		update(nod * 2 + 1,mid + 1,dr,S,D,val);
		
		aint[nod] = max(aint[2 * nod],aint[2 * nod + 1]);
	}
	
	int query(int nod,int st,int dr,int S,int D){
		propag(nod,st,dr);
		
		if(D < st || S > dr){
			return -1;
		}
		
		if(S <= st && dr <= D){
			return aint[nod];
		}
		
		int mid = (st + dr) / 2;
		return max(query(nod * 2,st,mid,S,D),query(nod * 2 + 1,mid + 1,dr,S,D));
	}
	
public:
	
	SegmentTree(vector<int> &base,bool enforce_throws = true){
		this->enforce_throws = enforce_throws;
		this->n = base.size();
		aint.resize(4 * n + 1);
		lazy.resize(4 * n + 1);
		build(1,0,n - 1,base);
	}
	
	SegmentTree(int n,bool enforce_throws = true){
		this->enforce_throws = enforce_throws;
		this->n = n;
		aint.resize(4 * n + 1);
		lazy.resize(4 * n + 1);
	}
	
	void update(int st,int dr,int val){
		if(enforce_throws && (st > dr || st < 0 || dr >= n)){
			throw runtime_error("invalid update");
		}
		update(1,0,n - 1,st,dr,val);
	}
	
	int query(int st,int dr){
		if(enforce_throws && (st > dr || st < 0 || dr >= n)){
			throw runtime_error("invalid update");
		}
		
		return query(1,0,n - 1,st,dr);
	}
	
	int overall_max(){
		return aint[1];
	}
	
	void print(){
		for(auto it:aint){
			printf("%d ",it);
		}
		printf("\n");
	}
};

const int NMAX = 1e5;

int n,q;

vector<int> graph[NMAX + 5];

int id[NMAX + 5],last_id = -1;
int sz[NMAX + 5];
int head[NMAX + 5];
int pos[NMAX + 5];
vector<SegmentTree> paths;
int heavy_son[NMAX + 5];

int lvl[NMAX + 5];
int father[NMAX + 5];

int v[NMAX + 5];
int w[NMAX + 5];

void predfs(int nod,int tata){
	lvl[nod] = 1 + lvl[tata];
	w[nod] = 1;
	father[nod] = tata;
	
	for(auto it:graph[nod]){
		if(it != tata){
			predfs(it,nod);
			if(w[it] > w[heavy_son[nod]]){
				heavy_son[nod] = it;
			}
		}
	}
	
	w[tata] += w[nod];
}

void dfs(int nod,int tata){
	if(!id[nod]){
		id[nod] = ++last_id;
		head[last_id] = nod;
		pos[nod] = 0;
	}
	
	sz[id[nod]]++;
	
	for(auto it:graph[nod]){
		if(it == tata){
			continue;
		}
		
		if(it == heavy_son[nod]){
			id[it] = id[nod];
			pos[it] = pos[nod] + 1;
		}
		
		dfs(it,nod);
	}
}

int main(){
	
	fscanf(f,"%d %d",&n,&q);
	
	for(int i = 1;i <= n;i++){
		fscanf(f,"%d",&v[i]);
	}
	
	for(int i = 1;i < n;i++){
		int x,y;
		fscanf(f,"%d %d",&x,&y);
		graph[x].push_back(y);
		graph[y].push_back(x);
	}
	
	predfs(1,0);
	dfs(1,0);
	
	for(int i = 0;i <= last_id;i++){
		paths.push_back(SegmentTree(sz[i]));
	}
	
	for(int i = 1;i <= n;i++){
		paths[id[i]].update(pos[i],pos[i],v[i]);
	}

	
	while(q--){
		int c,x,y;
		fscanf(f,"%d %d %d",&c,&x,&y);
		
		if(c == 0){
			paths[id[x]].update(pos[x],pos[x],y - v[x]);
			v[x] = y;
		}

		else{
			int ans = 0;
			while(id[x] != id[y]){
				if(lvl[head[id[x]]] < lvl[head[id[y]]]){
					ans = max(ans,paths[id[y]].query(0,pos[y]));
					y = father[head[id[y]]];
				}
				else{
					ans = max(ans,paths[id[x]].query(0,pos[x]));
					x = father[head[id[x]]];
				}
			}
			
			if(pos[x] > pos[y]){
				swap(x,y);
			}
			
			ans = max(ans,paths[id[x]].query(pos[x],pos[y]));
			fprintf(g,"%d\n",ans);
		}
	}
	
	fclose(f);
	fclose(g);
	
	return 0;
}