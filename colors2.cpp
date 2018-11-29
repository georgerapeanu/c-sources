#include <cstdio>
#include <cassert>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

FILE *f = fopen("colors2.in","r");
FILE *g = fopen("colors2.out","w");

const int NMAX = 15e4;
const int MMAX = 25e4;

vector<pair<int,int> > aint[4 * NMAX + 5];
vector<int> nodes[NMAX + 5];

void reset(int nod,int st,int dr){
	aint[nod].clear();
	if(st == dr){
		return ;
	}
	int mid = (st + dr) / 2;
	reset(nod * 2,st,mid);
	reset(nod * 2 + 1,mid + 1,dr);
}

void up(int nod,int st,int dr,int S,int D,int x,int y){
	if(S <= st && dr <= D){
		aint[nod].push_back({x,y});
		return ;
	}
	if(dr < S || D < st){
		return ;
	}
	int mid = (st + dr) / 2;
	up(nod * 2,st,mid,S,D,x,y);
	up(nod * 2 + 1,mid + 1,dr,S,D,x,y);
}

struct dsu_node{
	int father;
	int weight;
	int low_dr;
};

struct dsu_upd{
	int x,y;
	int t;
	int w;
	int l;
};

struct DSU{
	dsu_node stuff[NMAX + 5];
	dsu_upd changes[MMAX + 5];
	int len;
	
	DSU(){
		memset(stuff,0,sizeof(stuff));
		len = 0;
	}
	
	int fi(int nod){
		if(!stuff[nod].father){
			return nod;
		}
		return fi(stuff[nod].father);
	}
	
	void u(int x,int y){
		x = fi(x);
		y = fi(y);
		
		if(x == y){
			changes[++len] = {x,x,0,0,0};
			return ;
		}
		
		if(stuff[x].weight > stuff[y].weight){
			swap(x,y);
		}
		changes[++len] = {x,y,stuff[x].father,stuff[y].weight,stuff[y].low_dr};
		stuff[x].father = y;
		stuff[y].weight = stuff[y].weight + (stuff[x].weight == stuff[y].weight);
		stuff[y].low_dr = min(stuff[y].low_dr,stuff[x].low_dr);
	}
	
	bool check(int node,int c){
		return stuff[fi(node)].low_dr == c;
	}
	
	void undo(){
		dsu_upd tmp = changes[len--];
		if(tmp.x == tmp.y){
			return;
		}
		stuff[tmp.x].father = tmp.t;
		stuff[tmp.y].weight = tmp.w;
		stuff[tmp.y].low_dr = tmp.l;
	}
};

DSU ja;

void dfs(int nod,int st,int dr,bool &ok){
	for(auto it:aint[nod]){
		ja.u(it.first,it.second);
	}
	
	if(st == dr){
		for(auto it:nodes[st]){
			if(!ja.check(it,st)){
				ok = false;
				for(auto it:aint[nod]){
					ja.undo();
				}
				return;
			}
		}
	}
	else if(ok){
		int mid = (st + dr) / 2;
		dfs(nod * 2,st,mid,ok);
		dfs(nod * 2 + 1,mid + 1,dr,ok);
	}
	
	for(auto it:aint[nod]){
		ja.undo();
	}
}


int a[NMAX + 5];
int b[NMAX + 5];

int main(){
	
	int t;
	fscanf(f,"%d",&t);
	
	while(t--){
		assert(ja.len == 0);
		int n,m;
		bool ok = true;
		
		fscanf(f,"%d %d",&n,&m);
		
		for(int i = 1;i <= n;i++){
			fscanf(f,"%d",&a[i]);
		}
		
		for(int i = 1;i <= n;i++){
			fscanf(f,"%d",&b[i]);
			nodes[b[i]].push_back(i);
			if(b[i] > a[i]){
				ok = false;
			}
		}
		
		for(int i = 1;i <= m;i++){
			int x,y;
			fscanf(f,"%d %d",&x,&y);
			if(ok && max(b[x],b[y]) <= min(a[x],a[y])){
				up(1,1,n,max(b[x],b[y]),min(a[x],a[y]),x,y);
			}
		}
		
		if(!ok){
			goto afis;
		}
		
		for(int i = 1;i <= n;i++){
			ja.stuff[i].low_dr = a[i];
		}
		
		dfs(1,1,n,ok);
		
		afis:;
		reset(1,1,n);
		for(int i = 1;i <= n;i++){
			nodes[i].clear();
		}
		fprintf(g,"%d\n",ok);
	}
	
	fclose(f);
	fclose(g);
	
	return 0;
}