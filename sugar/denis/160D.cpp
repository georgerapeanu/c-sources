#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int NMAX = 1e5;
const int MMAX = 1e5;
const int VMAX = 1e6;

int n,m;

struct edge_t {
    int x,y;
    int id;

    int to(int nod) {
        return x ^ y ^ nod;
    }
};

vector<edge_t> edges[VMAX + 5];

int tp[MMAX + 5];

vector<edge_t> graph[NMAX + 5];

int low[NMAX + 5];
int id[NMAX + 5],last_id;
bool viz[NMAX + 5];

int father[NMAX + 5];

int find_root(int nod) {
    if(father[nod] == 0) {
        return nod;
    }
    return father[nod] = find_root(father[nod]);
}

bool unite(int x,int y) {
    x = find_root(x);
    y = find_root(y);

    if(x == y) {
        return false;
    }

    father[x] = y;
    return true;
}

void dfs(int nod,int father_id) {
    id[nod] = low[nod] = ++last_id;
    viz[nod] = true;

    for(auto it:graph[nod]) {
        if(it.id == father_id) {
            continue;
        }
        if(viz[it.to(nod)] == false) {
            dfs(it.to(nod),it.id);
            low[nod] = min(low[nod],low[it.to(nod)]);
            if(low[it.to(nod)] == id[it.to(nod)]) {
                tp[it.id] = 2;
            }
            else {
                tp[it.id] = 1;
            }
        }
        else {
            low[nod] = min(low[nod],id[it.to(nod)]);
            tp[it.id] = 1;
        }
    }
}

int main() {

    scanf("%d %d",&n,&m);

    for(int i = 1; i <= m; i++) {
        int x,y,z;

        scanf("%d %d %d",&x,&y,&z);

        edges[z].push_back({x,y,i});
    }

    for(int i = 1; i <= VMAX; i++) {
        vector<int> nodes;
        for(auto it:edges[i]) {
            if(find_root(it.x) == find_root(it.y)) {
                tp[it.id] = 0;
            }
            else {
                nodes.push_back(find_root(it.x));
                nodes.push_back(find_root(it.y));
                graph[find_root(it.x)].push_back({find_root(it.x),find_root(it.y),it.id});
                graph[find_root(it.y)].push_back({find_root(it.y),find_root(it.x),it.id});
            }
        }
        for(auto it:nodes) {
            if(viz[it] == false) {
                dfs(it,0);
            }
        }

        for(auto it:nodes) {
            viz[it] = false;
            graph[it].clear();
            low[it] = id[it] = 0;
        }

        last_id = 0;

        for(auto it:edges[i]) {
            unite(it.x,it.y);
        }
    }

    for(int i = 1; i <= m; i++) {
        fputs(tp[i] == 0 ? "none\n":(tp[i] == 1 ? "at least one\n":"any\n"),stdout);
    }

    return 0;
}
