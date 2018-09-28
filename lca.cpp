#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

FILE *f = fopen("lca.in","r");
FILE *g = fopen("lca.out","w");

const int NMAX = 1e5;
const int LGMAX = 17;

vector<int> graph[NMAX + 5];

int n,k;
int liniarizare[2 * NMAX + 5],sz_lin;
int lg2[2 * NMAX + 5];
int fst_pos[NMAX + 5];
int lvl[NMAX + 5];
int RMQ[LGMAX + 1][2 * NMAX + 5];

void prelca(int nod,int tata){
	liniarizare[++sz_lin] = nod;
	fst_pos[nod] = sz_lin;
	lvl[nod] = 1 + lvl[tata];
	
	for(auto it:graph[nod]){
		if(it != tata){
			prelca(it,nod);
			liniarizare[++sz_lin] = nod;
		}
	}
}

void make_lca(){
	prelca(1,0);
	
	lg2[0] = -1;
	
	for(int i = 1;i <= sz_lin;i++){
		lg2[i] = 1 + lg2[i / 2];
		RMQ[0][i] = liniarizare[i];
	}
	
	for(int i = 1;i <= LGMAX;i++){
		for(int j = 1;j <= sz_lin;j++){
			RMQ[i][j] = RMQ[i - 1][j];
			
			if(j >= (1 << (i - 1))){
				RMQ[i][j] = (lvl[RMQ[i - 1][j]] < lvl[RMQ[i - 1][j - (1 << (i - 1))]] ? RMQ[i - 1][j] : RMQ[i - 1][j - (1 << (i - 1))]);
			}
			
			else{
				RMQ[i][j] = 0;
			}
		}
	}
}

int lca(int u,int v){
	u = fst_pos[u];
	v = fst_pos[v];
	
	if(u > v){
		swap(u,v);
	}
	
	return lvl[RMQ[lg2[v - u + 1]][v]] < lvl[RMQ[lg2[v - u + 1]][u + (1 << lg2[v - u + 1]) - 1]] ? 
		   RMQ[lg2[v - u + 1]][v] : RMQ[lg2[v - u + 1]][u + (1 << lg2[v - u + 1]) - 1];
}

int main(){

	fscanf(f,"%d %d\n",&n,&k);
	
	for(int i = 2;i <= n;i++){
		int x;
		fscanf(f,"%d\n",&x);
		graph[x].push_back(i);
		graph[i].push_back(x);
	}
	
	make_lca();
	
	for(int i = 1;i <= k;i++){
		int x,y;
		fscanf(f,"%d %d",&x,&y);
		fprintf(g,"%d\n",lca(x,y));
	}
	
	
	fclose(f);
	fclose(g);

    return 0;
}
