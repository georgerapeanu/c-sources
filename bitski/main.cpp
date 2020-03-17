#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

FILE *f = fopen("bitski.in","r");
FILE *g = fopen("bitski.out","w");

const int NMAX = 1000;
const int CMAX = 1000;

int c;
int n,root;
vector<pair<int,int> > graph[NMAX + 5];

int cnt_leaves;
int lmin = NMAX * CMAX;
int lmax = -NMAX * CMAX;

int bst_node[NMAX + 5];
int bst_dist[NMAX + 5];

void dfs(int nod,int tata,int dist = 0){
    bst_node[nod] = nod;
    bst_dist[nod] = 1;
    for(auto it:graph[nod]){
        if(it.first == tata){
            continue;
        }
        dfs(it.first,nod,dist + it.second);
        if(bst_dist[it.first] + 1 > bst_dist[nod]){
            bst_dist[nod] = 1 + bst_dist[it.first];
            bst_node[nod] = bst_node[it.first];
        }
    }

    if((tata != 0) == int(graph[nod].size())){
        lmin = min(lmin,dist);
        lmax = max(lmax,dist);
        cnt_leaves++;
    }
}

int main(){

    fscanf(f,"%d",&c);
    fscanf(f,"%d %d",&n,&root);

    for(int i = 1;i < n;i++){
        int u,v,w;
        fscanf(f,"%d %d %d",&u,&v,&w);
        graph[u].push_back({v,w});
        graph[v].push_back({u,w});
    }

    dfs(root,0);

    if(c == 1){
        fprintf(g,"%d\n",cnt_leaves);
        fprintf(g,"%d %d\n",lmin,lmax);
    }
    else{
        root = bst_node[root];
        dfs(root,0);
        fprintf(g,"%d\n",bst_dist[root] / 2);
    }

    fclose(f);
    fclose(g);

    return 0;
}
