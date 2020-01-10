#include <cstdio>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <cstring>

using namespace std;

FILE *f = fopen("zeroc.in","r");
FILE *g = fopen("zeroc.out","w");

const int NMAX = 2e3;
const int MMAX = 15000;
const int inf = 2e3 * 1e4 + 5;

struct edge_t {
    int a,b,c;
} edges[MMAX + 5];

vector<pair<int,int> > graph[NMAX + 5];
vector<pair<int,int> > graph2[NMAX + 5];

int n,m;
int lst;
int comp[NMAX + 5];
int id[NMAX + 5],lst_id;
int low[NMAX + 5];

int st[NMAX + 5],len;
bool in_st[NMAX + 5];
int repr[NMAX + 5];

void dfs(int nod) {
    low[nod] = id[nod] = ++lst_id;
    st[++len] = nod;
    in_st[nod] = true;
    for(auto it:graph[nod]) {
        if(id[it.first] == 0) {
            dfs(it.first);
            low[nod] = min(low[nod],low[it.first]);
        }
        else if(in_st[it.first]) {
            low[nod] = min(low[nod],low[it.first]);
        }
    }

    if(low[nod] == id[nod]) {
        lst++;
        while(len > 0 && st[len] != nod) {
            comp[st[len]] = lst;
            in_st[st[len]] = false;
            len--;
        }
        comp[st[len]] = lst;
        in_st[st[len]] = false;
        repr[lst] = st[len];
        len--;
    }
}

int dist[NMAX + 5];
bool inq[NMAX + 5];

void bell(int nod) {
    queue<int> q;
    q.push(nod);
    inq[nod] = true;
    dist[nod] = 0;

    while(!q.empty()) {
        int nod = q.front();
        q.pop();
        inq[nod] = false;
        for(auto it:graph[nod]) {
            if(comp[it.first] == comp[nod] && dist[it.first] > dist[nod] + it.second) {
                dist[it.first] = dist[nod] + it.second;
                if(inq[it.first] == false) {
                    inq[it.first] = true;
                    q.push(it.first);
                }
            }
        }
    }
}

int main() {

    fscanf(f,"%d %d",&n,&m);

    for(int i = 1; i <= m; i++) {
        int u,v,w;

        fscanf(f,"%d %d %d",&u,&v,&w);

        graph[u].push_back({v,w});
        edges[i] = {u,v,w};
    }

    for(int i = 1; i <= n; i++) {
        dist[i] = inf;
        if(comp[i] == 0) {
            dfs(i);
        }
    }

    for(int i = 1; i <= lst; i++) {
        bell(repr[i]);
    }

    int ans = 0;

    for(int i = 1; i <= m; i++) {
        if(comp[edges[i].a] == comp[edges[i].b] && dist[edges[i].a] - dist[edges[i].b] == -edges[i].c) {
            graph2[edges[i].a].push_back({edges[i].b,0});
            edges[i].c = inf;
        }
    }

    for(int i = 1; i <= n; i++) {
        swap(graph[i],graph2[i]);
        comp[i] = low[i] = id[i] = lst_id = lst = repr[i] = st[i] = in_st[i] = len = 0;
    }

    for(int i = 1; i <= n; i++) {
        if(comp[i] == 0) {
            dfs(i);
        }
    }

    for(int i = 1; i <= m; i++) {
        if(edges[i].c == inf && comp[edges[i].a] == comp[edges[i].b]) {
            ans++;
        }
    }

    fprintf(g,"%d\n",ans);

    fclose(f);
    fclose(g);

    return 0;
}
