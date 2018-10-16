#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

FILE *f = fopen("maxdist.in","r");
FILE *g = fopen("maxdist.out","w");

const int NMAX = 2e5;
const int LGMAX = 18;
int n,q;

pair<int,int> updates[NMAX + 5];

bool used[NMAX + 5];
int last_unused = 1;

int ans_x[NMAX + 5];
int ans_y[NMAX + 5];

vector<int> graph[NMAX + 5];
int lvl[NMAX + 5];

int liniarizare[2 * NMAX + 5],lin_sz;
int fst[NMAX + 5];
int RMQ[LGMAX + 1][2 * NMAX + 5];
int lg2[2 * NMAX + 5];

void dfs(int nod,int tata){
	lvl[nod] = 1 + lvl[tata];
	liniarizare[++lin_sz] = nod;
	fst[nod] = lin_sz;
	
	for(auto it:graph[nod]){
		if(it != tata){
			dfs(it,nod);
			liniarizare[++lin_sz] = nod;
		}
	}
}

inline int better_lca(int u,int v){
	return (lvl[u] < lvl[v] ? u:v);
}

void make_lca(){
	dfs(1,0);
	
	lg2[0] = -1;
	
	for(int i = 1; i <= lin_sz;i++){
		lg2[i] = 1 + lg2[i / 2];
	}
	
	for(int i = 1;i <= lin_sz;i++){
		RMQ[0][i] = liniarizare[i];
	}
	
	for(int i = 1;i <= LGMAX;i++){
		for(int j = 1;j <= lin_sz;j++){
			RMQ[i][j] = RMQ[i - 1][j];
			if(j >= (1 << (i - 1))){
				RMQ[i][j] = better_lca(RMQ[i][j],RMQ[i - 1][j - (1 << (i - 1))]);
			}
		}
	}
}

int lca(int u,int v){
	int st = fst[u];
	int dr = fst[v];
	
	if(st > dr){
		swap(st,dr);
	}
	
	
	int dist = lg2[dr - st + 1];
	return better_lca(RMQ[dist][st + (1 << dist) - 1],RMQ[dist][dr]);
}

inline int dist(int u,int v){
	return lvl[u] + lvl[v] - 2 * lvl[lca(u,v)];
}

pair<int,int> ends;

pair<int,int> better_dist(pair<int,int> a,pair<int,int> b){
	return dist(a.first,a.second) <= dist(b.first,b.second) ? b : a;
}

void solve(pair<int,int> updates[],int ans[],bool pre){
	int step_ans = 0;
	ends = make_pair(updates[1].first,updates[1].first);
	
	for(int i = 1;i <= n;i++){
		
		if(pre){
			step_ans = max(step_ans,dist(ends.first,ends.second));
			ans[updates[i].second] = step_ans;
		}
		
		ends = better_dist(ends,better_dist(make_pair(updates[i].first,ends.first),make_pair(updates[i].first,ends.second)));
		
		if(!pre){
			step_ans = max(step_ans,dist(ends.first,ends.second));
			ans[updates[i].second] = step_ans;
		}
	}		
}

int main(){
	
	fscanf(f,"%d %d",&n,&q);
	
	for(int i = 1;i < n;i++){
		int x,y;
		fscanf(f,"%d %d",&x,&y);
		graph[x].push_back(y);
		graph[y].push_back(x);
	}
	
	for(int i = 1;i <= n;i++){
		if(i <= q){
			fscanf(f,"%d",&updates[i].first);
			updates[i].second = i;
			used[updates[i].first] = 1;
		}
		else{
			while(used[last_unused]){
				last_unused++;
			}
			
			updates[i].first = last_unused;
			used[last_unused] = 1;
		}
	}
	
	make_lca();
		
	solve(updates,ans_y,0);
	reverse(updates + 1,updates + 1 + n);
	solve(updates,ans_x,1);
	
	for(int i = 1;i <= q;i++){
		fprintf(g,"%d %d\n",ans_x[i],ans_y[i]);
	}
	
	
	fclose(f);
	fclose(g);
	
	return 0;
}
