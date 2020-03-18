#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

FILE *f = fopen("negot.in","r");
FILE *g = fopen("negot.out","w");

const int NMAX = 1000;
const int MMAX = 40000;

int n,m,k;

int S = NMAX + MMAX + 3;
int D = NMAX + MMAX + 4;

struct edge_t {
    int from;
    int to;
    int cap;
    int flow;

    inline int other(int x) {
        return x ^ from ^ to;
    }
};

vector<int> graph[NMAX + MMAX + 5];

vector<edge_t> edges;

void add_edge(int u,int v,int cap) {
    graph[u].push_back(edges.size());
    edges.push_back({u,v,cap,0});
    graph[v].push_back(edges.size());
    edges.push_back({v,u,0,0});
}

int q[NMAX + MMAX + 5],stq,drq;
int father[NMAX + MMAX + 5];
bool viz[NMAX + MMAX + 5];

bool bfs(int s,int d) {
    for(int i = 1; i <= drq; i++) {
        viz[q[i]] = false;
    }

    q[stq = drq = 1] = s;
    viz[s] = true;

    father[s] = -1;

    while(stq <= drq) {
        int nod = q[stq++];
        if(nod == d) {
            continue;
        }
        for(auto it:graph[nod]) {
            if(edges[it].flow < edges[it].cap && viz[edges[it].other(nod)] == false) {
                viz[edges[it].other(nod)] = true;
                q[++drq] = edges[it].other(nod);
                father[edges[it].other(nod)] = it;
            }
        }
    }

    return viz[d];
}

int maxflow(int s,int d) {
    int ans = 0;

    while(bfs(s,d)) {
        for(auto it:graph[d]) {
            if(viz[edges[it].other(d)] && edges[it ^ 1].flow <= edges[it ^ 1].cap) {
                father[d] = it ^ 1;
                int fmin = 1e9;
                for(int nod = d; nod != s; nod = edges[father[nod]].other(nod)) {
                    fmin = min(fmin,edges[father[nod]].cap - edges[father[nod]].flow);
                }
                ans += fmin;
                for(int nod = d; nod != s; nod = edges[father[nod]].other(nod)) {
                    edges[father[nod]].flow += fmin;
                    edges[father[nod] ^ 1].flow -= fmin;
                }
            }
        }
    }

    return ans;
}


int main() {

    fscanf(f,"%d %d %d",&n,&m,&k);

    for(int i = 1; i <= n; i++) {
        add_edge(S,i,k);
        int len;
        fscanf(f,"%d\n",&len);
        for(int j = 1; j <= len; j++) {
            int val;
            fscanf(f,"%d",&val);
            add_edge(i,val + n,1);
        }
    }

    for(int i = 1; i <= m; i++) {
        add_edge(n + i,D,1);
    }

    fprintf(g,"%d\n",maxflow(S,D));

    fclose(f);
    fclose(g);

    return 0;
}
