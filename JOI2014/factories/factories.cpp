#include "factories.h"
#include <vector>
#include <algorithm>

using namespace std;

const int NMAX = 5e5;
const int QMAX = 1e5;
const int LMAX = 19;
const long long inf = 1LL << 60;

int n,q;
vector< pair<int,long long> > graph[NMAX + 5];
vector< pair<int,long long> > graph2[NMAX + 5];
int lvl[NMAX + 5];
int father[LMAX + 1][NMAX + 5];
long long cost[NMAX + 5];

int len;
int pos[NMAX + 5];

int dsu[NMAX + 5];

long long best[NMAX + 5][2];
bool tp[NMAX + 5][2];

int fi_root(int nod) {
    if(dsu[nod] == 0) {
        return nod;
    }
    return dsu[nod] = fi_root(dsu[nod]);
}

inline long long get_cost(int w,int u) {
    return cost[u] - cost[w];
}

void dfs(int nod,int tata,long long c) {
    father[0][nod] = tata;
    cost[nod] = c;
    pos[nod] = ++len;
    lvl[nod] = 1 + lvl[tata];

    for(auto it:graph[nod]) {
        if(it.first == tata) {
            continue;
        }
        dfs(it.first,nod,c + it.second);
    }
}

int lca(int x,int y) {
    if(lvl[x] > lvl[y]) {
        swap(x,y);
    }

    int diff = lvl[y] - lvl[x];

    for(int h = LMAX; h >= 0; h--) {
        if((diff >> h) & 1) {
            y = father[h][y];
        }
    }

    if(x == y) {
        return x;
    }

    for(int h = LMAX; h >= 0; h--) {
        if(father[h][x] != father[h][y]) {
            x = father[h][x];
            y = father[h][y];
        }
    }

    return father[0][x];
}

void dfs2(int nod,int tata,long long &ans) {
    for(auto it:graph2[nod]) {
        if(it.first == tata) {
            continue;
        }
        dfs2(it.first,nod,ans);
        best[nod][0] = min(best[nod][0],best[it.first][0] + it.second);
        best[nod][1] = min(best[nod][1],best[it.first][1] + it.second);
    }
    if(tp[nod][0] == true) {
        best[nod][0] = 0;
    }
    if(tp[nod][1] == true) {
        best[nod][1] = 0;
    }

    ans = min(ans,best[nod][0] + best[nod][1]);
}

void res(int nod,int tata) {
    dsu[nod] = 0;
    tp[nod][0] = tp[nod][1] = false;
    best[nod][0] = best[nod][1] = inf;

    for(auto it:graph2[nod]) {
        if(it.first == tata) {
            continue;
        }
        res(it.first,nod);
    }
    graph2[nod].clear();
}

void Init(int N, int A[], int B[], int D[]) {
    n = N;
    for(int i = 0; i < n - 1; i++) {
        A[i]++;
        B[i]++;
        graph[A[i]].push_back({B[i],D[i]});
        graph[B[i]].push_back({A[i],D[i]});
    }

    dfs(1,0,0);

    for(int h = 1; h <= LMAX; h++) {
        for(int i = 1; i <= n; i++) {
            father[h][i] = father[h - 1][father[h - 1][i]];
        }
    }

    for(int i = 1; i <= n; i++) {
        dsu[i] = 0;
        best[i][0] = best[i][1] = inf;
    }
}

long long Query(int S, int X[], int T, int Y[]) {

    vector<int> nodes;

    for(int i = 0; i < S; i++) {
        X[i]++;
        nodes.push_back(X[i]);
        tp[X[i]][0] = true;
    }

    for(int i = 0; i < T; i++) {
        Y[i]++;
        nodes.push_back(Y[i]);
        tp[Y[i]][1] = true;
    }

    sort(nodes.begin(),nodes.end(),[&](int a,int b) {
        return pos[a] < pos[b];
    });

    vector<pair<int,pair<int,int> > > events;

    for(int i = 1; i < (int)nodes.size(); i++) {
        events.push_back(make_pair(lvl[lca(nodes[i - 1],nodes[i])],make_pair(nodes[i - 1],nodes[i])));
    }

    sort(events.begin(),events.end());
    reverse(events.begin(),events.end());

    int root = 0;
    for(auto it:events) {
        it.second.first = fi_root(it.second.first);
        it.second.second = fi_root(it.second.second);
        int w = lca(it.second.first,it.second.second);

        if(it.second.first != w) {
            long long c = get_cost(w,it.second.first);
            graph2[w].push_back({it.second.first,c});
            graph2[it.second.first].push_back({w,c});
            dsu[it.second.first] = w;
        }
        if(it.second.second != w) {
            long long c = get_cost(w,it.second.second);
            graph2[w].push_back({it.second.second,c});
            graph2[it.second.second].push_back({w,c});
            dsu[it.second.second] = w;
        }

        root = w;
    }

    long long ans = inf;

    dfs2(root,0,ans);

    res(root,0);

    return ans;
}
