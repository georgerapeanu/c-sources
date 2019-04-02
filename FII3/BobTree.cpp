#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int NMAX = 1e5;
const int LGMAX = 17;

struct upd_t {
    int x,y,color;
};

vector<upd_t> aint[4 * NMAX + 5];

int queries[NMAX + 5];

int color[NMAX + 5];
int last[NMAX + 5];
int n,q;
vector<int> graph[NMAX + 5];

int lvl[NMAX + 5];

int rmq[LGMAX + 1][2 * NMAX + 5];
int lin[2 * NMAX + 5],len;

int lg2[2 * NMAX + 5];
int fst[NMAX + 5];

void lca_dfs(int nod,int tata) {
    lvl[nod] = 1 + lvl[tata];

    lin[++len] = nod;
    fst[nod] = len;

    for(auto it:graph[nod]) {
        if(it != tata) {
            lca_dfs(it,nod);
            lin[++len] = nod;
        }
    }
}

void lca_prep() {
    lg2[0] = -1;

    for(int i = 1; i <= len; i++) {
        lg2[i] = 1 + lg2[i >> 1];
    }

    for(int i = 1; i <= len; i++) {
        rmq[0][i] = lin[i];
    }

    for(int h = 1; h <= LGMAX; h++) {
        for(int i = 1; i <= len; i++) {
            rmq[h][i] = rmq[h - 1][i];
            if(i > (1 << (h - 1)) && lvl[rmq[h - 1][i - (1 << (h - 1))]] < lvl[rmq[h][i]]) {
                rmq[h][i] = rmq[h - 1][i - (1 << (h - 1))];
            }
        }
    }
}

int lca(int x,int y) {
    if(fst[x] > fst[y]) {
        swap(x,y);
    }
    int d = lg2[fst[y] - fst[x] + 1];
    int u = rmq[d][fst[y]];
    int v = rmq[d][fst[x] + (1 << d) - 1];

    return (lvl[u] < lvl[v] ? u:v);
}

int dist(int u,int v) {
    return lvl[u] + lvl[v] - 2 * lvl[lca(u,v)];
}

void update(int nod,int st,int dr,const int &S,const int &D,const upd_t &val) {
    if(dr < S || st > D) {
        return ;
    }

    if(S <= st && dr <= D) {
        aint[nod].push_back(val);
        return ;
    }

    int mid = (st + dr) / 2;

    update(nod * 2,st,mid,S,D,val);
    update(nod * 2 + 1,mid + 1,dr,S,D,val);
}

int x[NMAX + 5];
int y[NMAX + 5];

vector<upd_t> tmp;

void dfs(int nod,int st,int dr) {

    int st_id = tmp.size();

    for(auto it:aint[nod]) {
        int u = x[it.color];
        int v = y[it.color];
        int w = it.x;

        tmp.push_back({u,v,it.color});

        if(u == 0) {
            u = w;
        }
        if(v == 0) {
            v = w;
        }

        int distuv = dist(u,v);
        int distuw = dist(u,w);
        int distvw = dist(v,w);

        if(distuv >= distuw && distuv >= distvw) {
            u = u;
            v = v;
        }
        else if(distuw >= distuv && distuw >= distvw) {
            u = u;
            v = w;
        }
        else if(distvw >= distuv && distvw >= distuw) {
            u = v;
            v = w;
        }

        x[it.color] = u;
        y[it.color] = v;
    }

    if(st == dr) {
        if(queries[st]) {
            printf("%d\n",dist(x[queries[st]],y[queries[st]]));
        }
        return ;
    }

    int mid = (st + dr) / 2;

    dfs(nod * 2,st,mid);
    dfs(nod * 2 + 1,mid + 1,dr);

    while((int)tmp.size() > st_id) {
        x[tmp.back().color] = tmp.back().x;
        y[tmp.back().color] = tmp.back().y;
        tmp.pop_back();
    }
}

int main() {

    scanf("%d",&n);

    for(int i = 1; i <= n; i++) {
        scanf("%d",&color[i]);
    }

    for(int i = 1; i < n; i++) {
        int x,y;
        scanf("%d %d",&x,&y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    lca_dfs(1,0);
    lca_prep();

    scanf("%d",&q);

    for(int i = 1; i <= q; i++) {
        int t;
        scanf("%d",&t);

        if(t == 1) {
            int v,c;
            scanf("%d %d",&v,&c);
            update(1,1,q,last[v],i - 1, {v,v,color[v]});
            color[v] = c;
            last[v] = i;
        }
        else {
            scanf("%d",&queries[i]);
        }
    }

    for(int i = 1; i <= n; i++) {
        update(1,1,q,last[i],q, {i,i,color[i]});
    }

    dfs(1,1,q);

    return 0;
}
