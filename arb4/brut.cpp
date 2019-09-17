#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

FILE *f = fopen("arb4.in","r");
FILE *g = fopen("arb4.ok","w");

const int NMAX = 1e5;
const int MMAX = 2e5;

struct edge_t {
    int u,v,w;

    edge_t() {
        this->u = this->v = this->w = 0;
    }

    edge_t(int u,int v,int w) {
        this->u = u;
        this->v = v;
        this->w = w;
    }
};

int n,m;
edge_t edge[NMAX + 5];
edge_t new_edge[MMAX + 5];
vector<int> graph[NMAX + 5];
int id[NMAX + 5];

void dfs(int nod,int tata,int cul) {
    id[nod] = cul;
    for(auto it:graph[nod]) {
        if(it != tata) {
            dfs(it,nod,cul);
        }
    }
}

int main() {

    fscanf(f,"%d %d",&n,&m);

    for(int i = 1; i < n; i++) {
        int u,v,w;
        fscanf(f,"%d %d %d",&u,&v,&w);
        u++;
        v++;
        graph[u].push_back(v);
        graph[v].push_back(u);
        edge[i] = {u,v,w};
    }

    for(int i = 1; i <= m - (n - 1); i++) {
        fscanf(f,"%d %d %d",&new_edge[i].u,&new_edge[i].v,&new_edge[i].w);
        new_edge[i].u++;
        new_edge[i].v++;
    }

    for(int i = 1; i < n; i++) {

        dfs(edge[i].u,edge[i].v,1);
        dfs(edge[i].v,edge[i].u,2);

        int ans = -1;

        for(int i = 1; i <= m - (n - 1); i++) {
            if(id[new_edge[i].u] != id[new_edge[i].v]) {
                ans = ((ans == -1 || new_edge[ans].w > new_edge[i].w) ? i:ans);
            }
        }

        fprintf(g,"%d\n",(ans == -1 ? -1:ans + (n - 1) - 1));
    }


    fclose(f);
    fclose(g);

    return 0;
}
