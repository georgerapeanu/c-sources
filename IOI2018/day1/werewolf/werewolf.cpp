#include "werewolf.h"

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int NMAX = 2e5;
const int LGMAX = 19;

vector< vector<int> > graph;

vector< vector<int> > tree_untill;
vector< vector<int> > tree_from;

int father_untill[LGMAX][NMAX + 5];
int father_from[LGMAX][NMAX + 5];

int root_untill;
int root_from;

int fa[NMAX + 5];

vector<int> aint(1,0);
vector<int> leftson(1,0);
vector<int> rightson(1,0);
vector<int> root;

void aint_init(int nod,int st,int dr){
	root.push_back(nod);
	
	vector< pair< int,pair<int,int> > > build_order;
	build_order.push_back({nod,{st,dr}});
	
	int last_node = 1;
	
	for(int i = 0;i < (int)build_order.size();i++){
		auto it = build_order[i];
		int nod = it.first;
		int st = it.second.first;
		int dr = it.second.second;
		
		aint.push_back(0);
		
		if(st == dr){
			leftson.push_back(0);
			rightson.push_back(0);
		}
		
		else{
			leftson.push_back(++last_node);
			build_order.push_back({last_node,{st,(st + dr) / 2}});
			rightson.push_back(++last_node);
			build_order.push_back({last_node,{(st + dr) / 2 + 1,dr}});
		}
	}
}

int aint_u(int nod,int st,int dr,int pos,int val){
	aint.push_back(aint[nod] + val);
	leftson.push_back(leftson[nod]);
	rightson.push_back(rightson[nod]);
	int new_node = (int)aint.size() - 1;
	
	
	if(st == dr){
		return new_node;
	}
	
	
	int mid = (st + dr) / 2;
	
	if(pos <= mid){
		int fiu = aint_u(leftson[nod],st,mid,pos,val);
		leftson[new_node] = fiu;
	}
	else{
		int fiu = aint_u(rightson[nod],mid + 1,dr,pos,val);
		rightson[new_node] = fiu;
	}
	
	return new_node;
}

int aint_query(int nod,int st,int dr,int x,int y){
	if(dr < x || st > y){
		return 0;
	}
	
	if(x <= st && dr <= y){
		return aint[nod];
	}
	
	int mid = (st + dr) / 2;
	
	return aint_query(leftson[nod],st,mid,x,y) + aint_query(rightson[nod],mid + 1,dr,x,y);
}

bool aint_lrxy(int N,int l,int r,int x,int y){
	return (aint_query(root[y],1,N,l,r) - aint_query(root[x - 1],1,N,l,r)) != 0;
}

void aint_update(int st,int dr,int pos,int val){
	int new_root = aint_u(root.back(),st,dr,pos,val);
	root.push_back(new_root);
}

void dsu_init(int n){
	for(int i = 1;i <= n;i++){
		fa[i] = 0;
	}
}

int dsu_fi(int nod){
	if(!fa[nod]){
		return nod;
	}
	return fa[nod] = dsu_fi(fa[nod]);
}

void dsu_u(int x,int y){
	x = dsu_fi(x);
	y = dsu_fi(y);
	
	if(x == y){
		return ;
	}
	
	fa[x] = y;
}

void liniarize(int root, vector< vector<int> > &tree,vector<int> &liniarizare,vector<int> &fst_pos,vector<int> &lst_pos){
	fst_pos[root] = (int)liniarizare.size();
	liniarizare.push_back(root);
	
	for(auto it:tree[root]){
		liniarize(it,tree,liniarizare,fst_pos,lst_pos);
	}
	
	lst_pos[root] = (int)liniarizare.size() - 1;
}	

vector<int> check_validity(int N, vector<int> X, vector<int> Y,
								  vector<int> S, vector<int> E,
								  vector<int> L, vector<int> R) {
	
	int Q = S.size();
	int M = X.size();
	
	graph.resize(N + 5);
	tree_from.resize(N + 5);
	tree_untill.resize(N + 5);
	
	for(int i = 0;i < Q;i++){
		S[i]++;
		E[i]++;
		L[i]++;
		R[i]++;
	}
	
	for(int i = 0;i < M;i++){
		X[i]++;
		Y[i]++;
	}
	
	vector<int> A(Q);
	
	for(int i = 0;i < M;i++){
		graph[X[i]].push_back(Y[i]);
		graph[Y[i]].push_back(X[i]);
	}
	
	dsu_init(N);
	
	for(int i = 1;i <= N;i++){
		vector<int> roots;
		for(auto it:graph[i]){
			if(it < i){
				roots.push_back(dsu_fi(it));
			}
		}
		sort(roots.begin(),roots.end());
		roots.resize(unique(roots.begin(),roots.end()) - roots.begin());
		for(auto it:roots){
			dsu_u(it,i);
			tree_untill[i].push_back(it);
			father_untill[0][it] = i;
		}
	}
	
	root_untill = N;
	
	dsu_init(N);
	
	for(int i = N;i;i--){
		vector<int> roots;
		for(auto it:graph[i]){
			if(it > i){
				roots.push_back(dsu_fi(it));
			}
		}
		sort(roots.begin(),roots.end());
		roots.resize(unique(roots.begin(),roots.end()) - roots.begin());
		for(auto it:roots){
			dsu_u(it,i);
			tree_from[i].push_back(it);
			father_from[0][it] = i;
		}
	}
	
	root_from = 1;

	vector<int> liniarizare_untill(1,0), fst_pos_untill(N + 5), lst_pos_untill(N + 5);
	vector<int> liniarizare_from(1,0), fst_pos_from(N + 5), lst_pos_from(N + 5);
	
	liniarize(root_untill,tree_untill,liniarizare_untill, fst_pos_untill, lst_pos_untill);
	liniarize(root_from,tree_from,liniarizare_from, fst_pos_from, lst_pos_from);
		
	vector< pair<int,int> > combined;
	
	for(int i = 1;i <= N;i++){
		combined.push_back({fst_pos_from[liniarizare_untill[i]],i});
	}
	
	sort(combined.begin(),combined.end());

	aint_init(1,1,N);

	for(auto it:combined){
		aint_update(1,N,it.second,1);
	}
	
	for(int h = 1;h < LGMAX;h++){
		for(int i = 1;i <= N;i++){
			father_from[h][i] = father_from[h - 1][father_from[h - 1][i]];
			father_untill[h][i] = father_untill[h - 1][father_untill[h - 1][i]];
		}
	}
	
	for(int i = 0;i < Q;i++){
		
		if(S[i] < L[i]){
			A[i] = 0;
			continue;
		}
		
		if(E[i] > R[i]){
			A[i] = 0;
			continue;
		}
		
		int fst_untill, snd_untill, ancestor_untill;
		int fst_from, snd_from, ancestor_from;
		
		ancestor_untill = E[i];
		
		for(int h = LGMAX - 1;h >= 0;h--){
			if(father_untill[h][ancestor_untill] && father_untill[h][ancestor_untill] <= R[i]){
				ancestor_untill = father_untill[h][ancestor_untill];
			}
		}
		
		ancestor_from = S[i];
		
		for(int h = LGMAX - 1;h >= 0;h--){
			if(father_from[h][ancestor_from] && father_from[h][ancestor_from] >= L[i]){
				ancestor_from = father_from[h][ancestor_from];
			}
		}
		
		fst_untill = fst_pos_untill[ancestor_untill];
		snd_untill = lst_pos_untill[ancestor_untill];
		fst_from = fst_pos_from[ancestor_from];
		snd_from = lst_pos_from[ancestor_from];
			
		A[i] = aint_lrxy(N,fst_untill,snd_untill,fst_from,snd_from);
	}
	
	return A;
}
