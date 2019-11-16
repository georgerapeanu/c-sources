#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

const int NMAX = 5e5;
const int LGMAX = 19;

int n;
int k;

vector<int> graph[NMAX + 5];
vector<int> nodes[NMAX + 5];

int state[NMAX + 5];
int father[LGMAX + 5][NMAX + 5];
int lvl[NMAX + 5];
int merge_root[NMAX + 5];
bool seen[NMAX + 5];

void predfs(int nod,int tata) {
    father[0][nod] = tata;
    merge_root[nod] = 0;
    lvl[nod] = 1 + lvl[tata];
    for(auto it:graph[nod]) {
        if(it == tata) {
            continue;
        }
        predfs(it,nod);
    }
}

void prelca() {
    for(int h = 1; h <= LGMAX; h++) {
        for(int i = 1; i <= NMAX; i++) {
            father[h][i] = father[h - 1][father[h - 1][i]];
        }
    }
}

int lca(int x,int y) {
    if(lvl[x] > lvl[y]) {
        swap(x,y);
    }

    int diff = lvl[y] - lvl[x];

    for(int h = LGMAX; h >= 0; h--) {
        if((diff >> h) & 1) {
            y = father[h][y];
        }
    }

    if(x == y) {
        return x;
    }

    for(int h = LGMAX; h >= 0; h--) {
        if(father[h][x] != father[h][y]) {
            x = father[h][x];
            y = father[h][y];
        }
    }

    return father[0][x];
}

int col_root[NMAX + 5];

int fi_col_root(int node) {
    if(col_root[node] == 0) {
        return node;
    }
    return col_root[node] = fi_col_root(col_root[node]);
}

bool merge_cols(int u,int v) {
    u = fi_col_root(u);
    v = fi_col_root(v);

    if(u == v) {
        return false;
    }

    col_root[v] = u;

    return true;
}

int fi_merge_root(int node) {
    if(merge_root[node] == 0) {
        return node;
    }
    return merge_root[node] = fi_merge_root(merge_root[node]);
}

void do_merge(int node,int root) {
    node = fi_merge_root(node);
    while(lvl[root] < lvl[node]) {
        merge_cols(state[node],state[father[0][node]]);
        merge_root[node] = father[0][node];
        node = fi_merge_root(node);
    }
}

set<int> col_neighbors[NMAX + 5];

int main() {

    scanf("%d %d",&n,&k);

    for(int i = 1; i < n; i++) {
        int u,v;
        scanf("%d %d",&u,&v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    for(int i = 1; i <= n; i++) {
        scanf("%d",&state[i]);
        nodes[state[i]].push_back(i);
    }

    predfs(1,0);
    prelca();

    for(int i = 1; i <= k; i++) {
        if(nodes[i].empty()) {
            continue;
        }

        int u = nodes[i].back();

        for(auto it:nodes[i]) {
            u = lca(u,it);
        }

        for(auto it:nodes[i]) {
            do_merge(it,u);
        }
    }

    int cnt = 0;

    for(int col = 1; col <= k; col++) {
        for(auto it:nodes[col]) {
            for(auto it2:graph[it]) {
                if(fi_col_root(col) != fi_col_root(state[it2])) {
                    col_neighbors[fi_col_root(col)].insert(fi_col_root(state[it2]));
                }
            }
        }
    }

    for(int col = 1; col <= k; col++) {
        cnt += (col_neighbors[col].size() == 1);
    }

    printf("%d\n",(cnt != 1) * (cnt + 1) / 2);
    return 0;
}
