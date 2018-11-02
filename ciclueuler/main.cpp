#include <cstdio>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;
FILE *f = fopen("ciclueuler.in","r");
FILE *g = fopen("ciclueuler.out","w");
int N,M;
vector<pair<int,int> >  graph[100005];
bool U[500005];
int st[500005];
int len;
int gr[100005];
int nr;

const int MMAX = 5e5;

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

int main()
{
    fscanf(f,"%d %d",&N,&M);
    for(int i = 1;i <= M;i++){
        int x,y;
        fscanf(f,"%d %d",&x,&y);
        graph[x].push_back({y,i});
        graph[y].push_back({x,i});
        gr[x]++;
        gr[y]++;
    }
    for(int i = 1;i <= N;i++){
        nr += (gr[i] % 2 == 1);
    }
    if(nr){
        fprintf(g,"-1");
        return 0;
    }
	
	get_euler(1,1);
	
	for(auto it:euler){
		if(it.first.first){
			fprintf(g,"%d ",it.first.first);
		}
	}
	
    fclose(f);
    fclose(g);
    return 0;
}