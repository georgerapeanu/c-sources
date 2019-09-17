#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

FILE *f = fopen("arb4.in","r");
FILE *g = fopen("arb4.out","w");

const int NMAX = 1e5;
const int MMAX = 25e4;

struct edge_t {
    int u,v,w,id;

    edge_t() {
        this->u = this->v = this->w = this->id = 0;
    }

    edge_t(int u,int v,int w,int id) {
        this->u = u;
        this->v = v;
        this->w = w;
        this->id = id;
    }

    bool operator < (const edge_t &other)const {
        return w < other.w;
    }
};

int n,m;
vector<pair<int,int>> graph[NMAX + 5];
int prev_edge[NMAX + 5];
edge_t new_edge[MMAX + 5];
int fst[NMAX + 5];
int lst[NMAX + 5];
int len;
int ans[NMAX + 5];
int fa_edge[NMAX + 5];
int real_ans[NMAX + 5];

void dfs(int nod,int tata) {
    fst[nod] = ++len;
    prev_edge[nod] = tata;

    for(auto it:graph[nod]) {
        if(it.first == tata) {
            continue;
        }
        fa_edge[it.first] = it.second;
        dfs(it.first,nod);
    }
    lst[nod] = len;
}

int get_ant(int nod) {
    if(ans[nod] == -1) {
        return nod;
    }
    return prev_edge[nod] = get_ant(prev_edge[nod]);
}

void apply(int u,int v,int id) {

    int tmp = get_ant(v);

    while((fst[tmp] <= fst[u] && lst[u] <= lst[tmp]) == false) {
        ans[tmp] = id;
        tmp = get_ant(tmp);
    }

    tmp = get_ant(u);

    while((fst[tmp] <= fst[v] && lst[v] <= lst[tmp]) == false) {
        ans[tmp] = id;
        tmp = get_ant(tmp);
    }

}

int main() {

    fscanf(f,"%d %d",&n,&m);

    for(int i = 1; i < n; i++) {
        int u,v,w;
        fscanf(f,"%d %d %d",&u,&v,&w);
        u++;
        v++;
        graph[u].push_back({v,i});
        graph[v].push_back({u,i});
    }

    for(int i = 1; i <= n; i++) {
        ans[i] = -1;
    }

    m -= (n - 1);

    for(int i = 1; i <= m; i++) {
        int u,v,w;
        fscanf(f,"%d %d %d",&u,&v,&w);
        u++;
        v++;
        new_edge[i] = {u,v,w,i};
    }

    sort(new_edge + 1,new_edge + 1 + m);

    dfs(1,0);

    for(int i = 1; i <= m; i++) {
        apply(new_edge[i].u,new_edge[i].v,new_edge[i].id + (n - 1) - 1);
    }

    for(int i = 2; i <= n; i++) {
        real_ans[fa_edge[i]] = ans[i];
    }

    for(int i = 1; i < n; i++) {
        fprintf(g,"%d\n",real_ans[i]);
    }

    fclose(f);
    fclose(g);

    return 0;
}
