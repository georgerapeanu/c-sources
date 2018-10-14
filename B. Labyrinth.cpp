#define JUDGE 1

#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int NMAX = 2e3;

int n,m;
int l,r;
int x,y;

char c[NMAX + 5][NMAX + 5];

int type[NMAX + 5][NMAX + 5];
int size_of[NMAX * NMAX + 5];
int last_type;

vector< pair<int,int> > graph[NMAX * NMAX + 5];
vector< pair<int,int> > edges;

bool viz[NMAX * NMAX + 5][2];

int bfs(int nod,int x,int y){
	queue< pair<pair<int,int>,pair<int,int> > > Q;
	int ans = size_of[nod];
	viz[nod][0] = 1;
	Q.push(make_pair(make_pair(nod,0),make_pair(x,y)));
	
	while(!Q.empty()){
		int nod = Q.front().first.first;
		int wh = Q.front().first.second;
		int x = Q.front().second.first;
		int y = Q.front().second.second;
		Q.pop();
		
		for(auto it:graph[nod]){
			if(it.second == 0 && !viz[it.first][0] && x){
				Q.push(make_pair(make_pair(it.first,0),make_pair(x - 1,y)));
				ans += (viz[it.first][1] == 0) * size_of[it.first];
				viz[it.first][0] = 1;
			}
			if(it.second == 1 && !viz[it.first][1] && y){
				Q.push(make_pair(make_pair(it.first,1),make_pair(x,y - 1)));
				ans += (viz[it.first][0] == 0) * size_of[it.first];
				viz[it.first][1] = 1;
			}
		}
	}
	return ans;
}

int main(){
	
	if(!JUDGE){
		freopen("in","r",stdin);
		freopen("out","w",stdout);
	}
	
	
	fscanf(stdin,"%d %d\n",&n,&m);
	fscanf(stdin,"%d %d\n",&l,&r);
	fscanf(stdin,"%d %d\n",&x,&y);
	
	for(int i = 1;i <= n;i++){
		fgets(c[i] + 1,m + 5,stdin);
	}
	
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){
			if(c[i][j] == '*'){
				continue;
			}
			
			if(type[i - 1][j]){
				type[i][j] = type[i - 1][j];
				size_of[type[i][j]]++;
			}
			
			else{
				type[i][j] = ++last_type;
				size_of[type[i][j]]++;
			}
			
			if(type[i][j - 1] && type[i][j]){
				edges.push_back(make_pair(type[i][j - 1],type[i][j]));
			}
		}
	}
	
	sort(edges.begin(),edges.end());
	edges.resize(unique(edges.begin(),edges.end()) - edges.begin());
	
	for(auto it:edges){
		graph[it.first].push_back({it.second,1});
		graph[it.second].push_back({it.first,0});
	}
	
	fprintf(stdout,"%d",bfs(type[l][r],x,y));
	
	
	return 0;
}