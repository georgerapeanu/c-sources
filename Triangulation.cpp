#include <iostream>
#include <cstdio>
#include <cassert>
#include <algorithm>
#include <map>
#include <queue>
#include <vector>

using namespace std;

int N;
map< pair<int,int> , vector< int > > common_edge;
vector<int> G[100005];
vector<int> nodes_with_color[100005];
int T[18][100005];
int lvl[100005];

vector<int> liniarizare;
int fst[100005];
int lst[100005];

int AIB[200005];

void u(int pos,int val){
	for(;pos < (int)liniarizare.size();pos += (-pos) & pos){
		AIB[pos] += val;
	}
}

vector<int> get_AIB_values(){
	vector<int> ans(liniarizare.size());
	queue< pair<int,pair<int,int> > > Q;
	
	Q.push({0,{0,17}});
	
	while(!Q.empty()){
		pair<int,pair<int,int> > tmp = Q.front();
		Q.pop();
		
		if(tmp.second.second < 0){
			ans[tmp.second.first] = tmp.first;
			continue;
		}
		
		pair<int,pair<int,int> > a,b;
		
		a = tmp;
		a.second.second--;
		
		Q.push(a);
		
		b = tmp;
		if(b.second.first + (1 << b.second.second) < (int)liniarizare.size()){
			b.second.first = b.second.first + (1 << b.second.second);
			b.first += AIB[b.second.first];
			b.second.second--;
			Q.push(b);
		}
	}
	
	return ans;
}

void dfs(int nod,int tata){
	fst[nod] = liniarizare.size();
	liniarizare.push_back(nod);
	
	lvl[nod] = 1 + lvl[tata];
	T[0][nod] = tata;
	for(auto it:G[nod]){
		if(it != tata){
			dfs(it,nod);
		}
	}
	
	lst[nod] = liniarizare.size();
	liniarizare.push_back(nod);
}

void prelca(){
	for(int lg = 1;lg <= 17;lg++){
		for(int i = 1;i < N - 1;i++){
			T[lg][i] = T[lg - 1][T[lg - 1][i]];
		}
	}
}

int lca(int u,int v){
	if(lvl[u] > lvl[v]){
		swap(u,v);
	}
	
	int dif = lvl[v] - lvl[u];
	
	for(int lg = 17;lg >= 0;lg--){
		if((dif >> lg) & 1){
			v = T[lg][v];
		}
	}
	
	if(u == v){
		return u;
	}
	
	for(int lg = 17;lg >= 0;lg--){
		if(T[lg][u] != T[lg][v]){
			u = T[lg][u];
			v = T[lg][v];
		}
	}
	
	return T[0][u];
}

int main(){
	
	///freopen("trian01.in","r",stdin);
	
	cin >> N;
	for(int i = 1;i < N - 1;i++){
		int A,B,C,D;
		cin >> A >> B >> C >> D;
		
		vector<int> tmp = {A,B,C};
		sort(tmp.begin(),tmp.end());
	
		A = tmp[0];
		B = tmp[1];
		C = tmp[2];
		
		
		common_edge[{A,B}].push_back(i);
		common_edge[{A,C}].push_back(i);
		common_edge[{B,C}].push_back(i);
		nodes_with_color[D].push_back(i);
	}
	
	for(auto it:common_edge){
		assert(it.second.size() <= 2);
		if(it.second.size() > 1){
			G[it.second[0]].push_back(it.second[1]);
			G[it.second[1]].push_back(it.second[0]);
		}
	}
	
	liniarizare.push_back(0);
	
	dfs(1,0);
	prelca();
	
	for(int i = 1;i <= N;i++){
		if(nodes_with_color[i].empty()){
			continue;
		}
		int top_node = nodes_with_color[i][0];
		for(int j = 1;j < (int)nodes_with_color[i].size();j++){
			top_node = lca(top_node,nodes_with_color[i][j]);
		}
		
		for(auto it:nodes_with_color[i]){
			u(fst[top_node] + 1,1);
			u(fst[it] + 1,-1);
		}
	}
	
	vector<int> real_values = get_AIB_values();
	
	int ans = 0;
	
	for(int i = 2;i < N - 1;i++){
		if(real_values[fst[i]] - real_values[lst[i]] == 0){
			ans++;
		}
	}
	
	cout << ans;
	
	return 0;
}