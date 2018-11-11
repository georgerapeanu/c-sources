#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

const int NMAX = 2e5;
const int LGMAX = 18;

int n,q;

vector<int> graph[NMAX + 5];

int liniarizare[NMAX + 5],sz;
int fst[NMAX + 5],lst[NMAX + 5];

void dfs(int nod,int tata){
	liniarizare[++sz] = nod;
	fst[nod] = sz;
	
	for(auto it:graph[nod]){
		if(it != tata){
			dfs(it,nod);
		}
	}
	
	lst[nod] = sz;
}

int T[LGMAX + 1][NMAX + 5];
int lvl[NMAX + 5];

void lca_dfs(int nod,int tata){
	lvl[nod] = 1 + lvl[tata];
	T[0][nod] = tata;
	
	for(auto it:graph[nod]){
		if(it != tata){
			lca_dfs(it,nod);
		}
	}
}

void make_lca(){
	lca_dfs(1,0);
	
	for(int i = 1;i <= LGMAX;i++){
		for(int j = 1;j <= n;j++){
			T[i][j] = T[i - 1][T[i - 1][j]];
		}
	}
}

pair<int,int> lca(int x,int y){
	
	for(int i = LGMAX;i >= 0;i--){
		if(lvl[y] - lvl[x] > (1 << i)){
			y = T[i][y];
		}
	}
	
	if(T[0][y] == x){
		return {x,y};
	}
	
	y = T[0][y];
	
	for(int i = LGMAX;i >= 0;i--){
		if(T[i][x] != T[i][y]){
			x = T[i][x];
			y = T[i][y];
		}
	}
	
	return {T[0][x],y};
}

set<pair<int,int> > edges;

struct node_t{
	int lazy;
	int st,dr;
	int fr_st;
	
	node_t(){
		lazy = 0;
		st = dr = 0;
		fr_st = 0;
	}
	
	node_t(int lazy,int st,int dr,int fr_st){
		this->lazy = lazy;
		this->st = st;
		this->dr = dr;
		this->fr_st = fr_st;
	}
	
	node_t operator + (const node_t &other)const{
		node_t ans;
		ans.lazy = 0;
		ans.st = min(this->st,other.st);
		ans.dr = max(this->dr,other.dr);
		ans.fr_st = (this->st == ans.st) * this->fr_st + (other.st == ans.st) * other.fr_st;
		return ans;
	}
	
	node_t operator + (const int delta)const{
		node_t ans = *this;
		ans.st += delta;
		ans.dr += delta;
		ans.lazy += delta;
		return ans;
	}
};

node_t aint[4 * NMAX + 5];

void build(int nod,int st,int dr){
	aint[nod] = node_t(0,0,0,1);
	
	if(st == dr){
		return ;
	}
	
	int mid = (st + dr) / 2;
	
	build(nod * 2,st,mid);
	build(nod * 2 + 1,mid + 1,dr);
	aint[nod] = aint[2 * nod] + aint[2 * nod + 1];
}

void propag(int nod,int st,int dr){
	if(st == dr || !aint[nod].lazy){
		aint[nod].lazy = 0;
		return ;
	}
	
	aint[2 * nod] = aint[2 * nod] + aint[nod].lazy;
	aint[2 * nod + 1] = aint[2 * nod + 1] + aint[nod].lazy;
	aint[nod].lazy = 0;
}

void update(int nod,int st,int dr,int S,int D,int val){
	
	propag(nod,st,dr);
	
	if(D < st || S > dr){
		return ;
	}
	
	if(S <= st && dr <= D){
		aint[nod] = aint[nod] + val;
		return ;
	}
	
	int mid = (st + dr) / 2;
	
	update(nod * 2,st,mid,S,D,val);
	update(nod * 2 + 1,mid + 1,dr,S,D,val);
	
	aint[nod] = aint[2 * nod] + aint[2 * nod + 1];
}

int get_ans(){
	return aint[1].fr_st * (aint[1].st == 0);
}

void baga(vector< pair<int,int> > &segm,int sgn){
	sort(segm.begin(),segm.end());
	if(segm[0].first != 1)update(1,1,n,1,segm[0].first - 1,sgn);
	if(segm.back().second != n)update(1,1,n,segm.back().second + 1,n,sgn);
	if(segm[0].second + 1 <= segm[1].first - 1)update(1,1,n,segm[0].second + 1,segm[1].first - 1,sgn);
		
	if(segm.size() > 2){
		if(segm[1].second + 1 <= segm[2].first - 1)update(1,1,n,segm[1].second + 1,segm[2].first - 1,sgn);
	}
}

int main(){
	
	scanf("%d %d",&n,&q);
	
	for(int i = 1;i < n;i++){
		int x,y;
		scanf("%d %d",&x,&y);
		graph[x].push_back(y);
		graph[y].push_back(x);
	}
	
	dfs(1,0);
	make_lca();
	build(1,1,n);
		
	while(q--){
		int x,y;
		scanf("%d %d",&x,&y);
		
		if(lvl[x] > lvl[y] || (lvl[x] == lvl[y] && x > y)){
			swap(x,y);
		}
		
		pair<int,int> tmp = lca(x,y);
		int w = tmp.first;
				
		vector< pair<int,int> >	segm;
		
		if(w == x){
			if(fst[tmp.second] != 1)segm.push_back({1,fst[tmp.second] - 1});
			if(lst[tmp.second] + 1 <= sz)segm.push_back({lst[tmp.second] + 1,sz});
			segm.push_back({fst[y],lst[y]});
		}
		
		else{
			segm.push_back({fst[x],lst[x]});
			segm.push_back({fst[y],lst[y]});
		}
		
		if(edges.count({x,y})){
			edges.erase({x,y});
			baga(segm,-1);
		}
		else{
			edges.insert({x,y});
			baga(segm,1);
		}
		
		printf("%d\n",get_ans());
	}
	
	return 0;
}