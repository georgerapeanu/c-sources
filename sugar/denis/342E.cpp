#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int NMAX = 1e5;
const int QMAX = 1e5;
const int LGMAX = 17;
const int BUCK = 320;

int n,q;

int d[NMAX + 5];
int father[LGMAX + 1][NMAX + 5];
int lvl[NMAX + 5];
pair<int,int> v[QMAX + 5];
vector<int> graph[NMAX + 5];

void dfs_lca(int nod,int tata) {
    father[0][nod] = tata;
    lvl[nod] = 1 + lvl[tata];
    for(auto it:graph[nod]) {
        if(it != tata) {
            dfs_lca(it,nod);
        }
    }
}

void make_lca() {
    dfs_lca(1,0);

    for(int h = 1; h <= LGMAX; h++) {
        for(int i = 1; i <= n; i++) {
            father[h][i] = father[h - 1][father[h - 1][i]];
        }
    }
}

int lca(int x,int y) {
    if(lvl[x] > lvl[y]) {
        swap(x,y);
    }

    for(int h = LGMAX; h >= 0; h--) {
        if((lvl[y] - lvl[x]) >> h) {
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

int dist(int x,int y) {
    return lvl[x] + lvl[y] - 2 * lvl[lca(x,y)];
}

void bfs(vector<int> &nodes) {
    for(int i = 1; i <= n; i++) {
        d[i] = n + 1;
    }

    vector<int> bf;

    for(auto it:nodes) {
        d[it] = 0;
        bf.push_back(it);
    }

    for(int i = 0; i < (int)bf.size(); i++) {
        for(auto it:graph[bf[i]]) {
            if(d[it] > d[bf[i]] + 1) {
                d[it] = d[bf[i]] + 1;
                bf.push_back(it);
            }
        }
    }

}

int main() {

    scanf("%d %d",&n,&q);

    for(int i = 1; i < n; i++) {
        int x,y;
        scanf("%d %d",&x,&y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    make_lca();

    vector<int> reds;

    v[1] = {1,1};
    q++;

    for(int i = 2; i <= q; i++) {
        scanf("%d %d",&v[i].first,&v[i].second);
    }

    for(int i = 1; i <= q; i += BUCK) {
        bfs(reds);
        for(int j = i; j < i + BUCK && j <= q; j++) {
            if(v[j].first == 2) {
                int ans = d[v[j].second];
                for(int k = i; k < j; k++) {
                    if(v[k].first == 1) {
                        ans = min(ans,dist(v[j].second,v[k].second));
                    }
                }
                printf("%d\n",ans);
            }
            else {
                reds.push_back(v[j].second);
            }
        }

    }

    return 0;
}
