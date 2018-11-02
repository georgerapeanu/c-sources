#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int NMAX = 2e5;
const int MMAX = 5e5;


vector< pair<int,int> > graph[NMAX + 5];
int gr[NMAX + 5];

int ans[NMAX + 5];

vector<pair<pair<int,int>,int> > euler;
bool used[MMAX + 5];

void get_euler(int node,bool dump){
	if(dump){
		euler.clear();
	}
	
	vector<pair<int,pair<pair<int,int>,int> > > st;
	
	st.push_back({node,{{0,0},0}});
	
	while(!st.empty()){
		node = st.back().first;
		pair<pair<int,int>,int> edge = st.back().second;
		
		while(!graph[node].empty() && used[graph[node].back().second]){
			graph[node].pop_back();
		}
		
		if(graph[node].empty()){
			euler.push_back(edge);
			st.pop_back();
		}
		else{
			int it = graph[node].back().first;
			int id = graph[node].back().second;
			graph[node].pop_back();
			used[id] = true;
			st.push_back(make_pair(it,make_pair(make_pair(node,it),id)));
		}
	}
}

void solve(vector< pair<pair<int,int>,int> > &edges,int &last_cul){
	int ma = 0;
	for(auto it:edges){
		gr[it.first.first]++;
		gr[it.first.second]++;
		
		graph[it.first.first].push_back({it.first.second,it.second});
		graph[it.first.second].push_back({it.first.first,it.second});
		
		ma = max(ma,gr[it.first.first]);
		ma = max(ma,gr[it.first.second]);
	}
	
	if(ma <= 1){
		last_cul++;
		for(auto it:edges){
			ans[it.second] = last_cul;
			gr[it.first.first] = 0;
			gr[it.first.second] = 0;
			graph[it.first.first].clear();
			graph[it.first.second].clear();
		}
		return ;
	}
	
	int fst_virtual = NMAX + 1;
	int snd_virtual = NMAX + 2;
	
	for(auto it:edges){
		if(gr[it.first.first] % 2 == 1){
			gr[it.first.first]++;
			gr[snd_virtual]++;
			
			graph[it.first.first].push_back({snd_virtual,0});
			graph[snd_virtual].push_back({it.first.first,0});
		}
		
		if(gr[it.first.second] % 2 == 1){
			gr[it.first.second]++;
			gr[fst_virtual]++;
			
			graph[it.first.second].push_back({fst_virtual,0});
			graph[fst_virtual].push_back({it.first.second,0});
		}
	}
	
	used[0] = false;
	
	for(auto it:edges){
		used[it.second] = false;
	}
	
	get_euler(fst_virtual,1);
	get_euler(snd_virtual,0);
	
	for(auto it:edges){
		get_euler(it.first.first,0);
		get_euler(it.first.second,0);
	}
	
	vector<pair<pair<int,int>,int> > x[2];
	
	for(int i = 0;i < (int)euler.size();i++){
		if(!euler[i].second){
			continue;
		}	
		x[i & 1].push_back(euler[i]);
	}
	
	for(auto it:edges){
		gr[it.first.first] = 0;
		gr[it.first.second] = 0;
		graph[it.first.second].clear();
		graph[it.first.first].clear();
	}
	
	graph[fst_virtual].clear();gr[fst_virtual] = 0;
	graph[snd_virtual].clear();gr[snd_virtual] = 0;
	
	solve(x[0],last_cul);
	solve(x[1],last_cul);
}

int main(){
	int l,r,m;
	
	scanf("%d %d %d",&l,&r,&m);
	
	vector<pair<pair<int,int>,int> > edges;
	
	for(int i = 1;i <= m;i++){
		int x,y;
		scanf("%d %d",&x,&y);
		y += l;
		edges.push_back({{x,y},i});
	}
	
	int last_cul = 0;
	
	solve(edges,last_cul);
	
	printf("%d\n",last_cul);
	
	for(int i = 1;i <= m;i++){
		printf("%d\n",ans[i]);
	}
	
	return 0;
}