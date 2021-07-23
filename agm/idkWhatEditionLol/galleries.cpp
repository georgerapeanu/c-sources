#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5;
const int MMAX = 2e5;
const int LGMAX = 16;

int n,m;
vector<int> graph[NMAX + 5];
pair<int,int> nodes[NMAX + 5];

int dsu[NMAX + 5];
int weight[NMAX + 5];
int val[NMAX + 5];

int father[LGMAX + 1][NMAX + 5];

int fi_root(int x) {
    if(dsu[x] == 0) {
        return x;
    }
    return dsu[x] = fi_root(dsu[x]);
}

bool unite(int x,int y) {
    x = fi_root(x);
    y = fi_root(y);

    if(x == y) {
        return false;
    }

    dsu[x] = y;
    return true;
}


int main() {

    scanf("%d %d",&n,&m);

    for(int i = 1; i <= n; i++) {
        scanf("%d",&nodes[i].first);
        nodes[i].second = i;
        val[i] = nodes[i].first;
    }

    for(int i = 1; i <= m; i++) {
        int x,y;
        scanf("%d %d",&x,&y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    sort(nodes + 1,nodes + 1 + n);

    for(int i = 1; i <= n; i++) {
        int nod = nodes[i].second;
        weight[nod] = 1;

        for(auto it:graph[nod]) {
            if(weight[it]) {
                if(fi_root(it) != fi_root(nod)) {
                    father[0][fi_root(it)] = fi_root(nod);
                    weight[fi_root(nod)] += weight[fi_root(it)];
                    unite(it,nod);
                }
            }
        }
    }

    weight[0] = n + 5;

    for(int h = 1; h <= LGMAX; h++) {
        for(int i = 1; i <= n; i++) {
            father[h][i] = father[h - 1][father[h - 1][i]];
        }
    }

    int q;

    scanf("%d",&q);

    while(q--) {
        int x,k;
        scanf("%d %d",&x,&k);
        if(weight[x] >= k) {
            printf("%d\n",val[x]);
        }
        else {
            for(int h = LGMAX; h >= 0; h--) {
                if(weight[father[h][x]] < k) {
                    x = father[h][x];
                }
            }
            x = father[0][x];
            printf("%d ",val[x]);
        }
    }

    return 0;
}
