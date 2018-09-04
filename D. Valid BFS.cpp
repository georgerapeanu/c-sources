#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>

using namespace std;

FILE *f = stdin;
FILE *g = stdout;

const int NMAX = 2e5;

int n;
set<pair<int,int> > edges;
vector<int> graph[NMAX + 5];
vector<int> order;
vector<int> pos_order;

vector<int> dists;
vector<int> bfs;

int main(){
	
	fscanf(f,"%d",&n);
	
	dists.resize(n + 5);
	pos_order.resize(n + 5);
	
	for(int i = 1;i < n;i++){
		int x,y;
		fscanf(f,"%d %d",&x,&y);
		graph[x].push_back(y);
		graph[y].push_back(x);
	}
	
	for(int i = 1;i <= n;i++){
		int val;
		fscanf(f,"%d",&val);
		order.push_back(val);
		pos_order[val] = i;
	}
	
	
	bfs.push_back(1);
	dists[1] = 1;
	
	for(int i = 0;i < (int)bfs.size();i++){
		int nod = bfs[i];
		sort(graph[nod].begin(),graph[nod].end(),[&](int a,int b){return pos_order[a] < pos_order[b];});
		for(auto it:graph[nod]){
			if(!dists[it]){
				dists[it] = dists[nod] + 1;
				bfs.push_back(it);
			}
		}
	}
	
	for(int i = 0;i < n - 1;i++){
		if(bfs[i] != order[i]){
			fputs("No\n",g);
			return 0;
		}
	}
	
	fputs("Yes\n",g);
	
	return 0;
}