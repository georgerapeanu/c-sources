#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

FILE *f = fopen("viteza2.in","r");
FILE *g = fopen("viteza2.out","w");

struct edge_t{
    int u,v,w;
    bool operator < (const edge_t &other)const{
        return w < other.w;
    }
};


const int NMAX = 1e3;
const int inf = 1e9 + 10;
int n,m;
int dist[NMAX + 5][NMAX + 5];
vector<edge_t> edges;

int main(){
    
    fscanf(f,"%d %d",&n,&m);

    for(int i = 1;i <= m;i++){
        edge_t tmp;
        fscanf(f,"%d %d %d",&tmp.u,&tmp.v,&tmp.w);
        edges.push_back(tmp);
    }

    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            dist[i][j] = inf * (i != j);
        }
    }

    sort(edges.begin(),edges.end());

    for(auto it:edges){
        for(int i = 1;i <= n;i++){
            dist[i][it.v] = min(dist[i][it.v],dist[i][it.u] + it.w);
            dist[i][it.u] = min(dist[i][it.u],dist[i][it.v] + it.w);
        }
    }

    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            if(dist[i][j] == inf){
                dist[i][j] = -1;
            }
            fprintf(g,"%d ",dist[i][j]);
        }
        fprintf(g,"\n");
    }

    fclose(f);
    fclose(g);

    return 0;
}
