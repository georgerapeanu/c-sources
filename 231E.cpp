#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

FILE *f = stdin;
FILE *g = stdout;

const int MOD = 1e9 + 7;
const int NMAX = 1e5;
const int MMAX = 1e5;
const int LGMAX = 17;

int n,m,q;

vector<int> graph[NMAX + 5];

int remap[NMAX + 5],last_id = 0;

pair<int,int> edges[MMAX + 5];

vector<int> st;
bool in_st[NMAX + 5];
bool special[NMAX + 5];
bool viz[NMAX + 5];
int pre[NMAX + 5];

void get_cycles(int nod,int tata) {
    st.push_back(nod);
    in_st[nod] = true;
    viz[nod] = true;

    bool found = false;

    for(auto it:graph[nod]) {
        if(it == tata) {
            continue;
        }

        if(viz[it]) {
            if(!in_st[it]) {
                continue;
            }

            last_id++;

            int ind = (int)st.size() - 1;

            while(st[ind] != it) {
                remap[st[ind]] = last_id;
                ind--;
            }
            remap[st[ind]] = last_id;
            special[last_id] = true;
        }
        else {
            get_cycles(it,nod);
        }
    }

    if(!found && !remap[nod]) {
        remap[nod] = ++last_id;
    }

    in_st[nod] = false;
    st.pop_back();
}

int father[LGMAX + 1][NMAX + 5];
int cnt[NMAX + 5];
int lvl[NMAX + 5];

void dfs(int nod,int tata) {
    lvl[nod] = 1 + lvl[tata];
    cnt[nod] = special[nod] + cnt[tata];
    father[0][nod] = tata;

    for(auto it:graph[nod]) {
        if(it != tata) {
            dfs(it,nod);
        }
    }
}

int lca(int x,int y) {
    if(lvl[x] > lvl[y]) {
        swap(x,y);
    }

    int delta = lvl[y] - lvl[x];

    for(int i = LGMAX; i >= 0; i--) {
        if(delta >> i) {
            delta ^= (1 << i);
            y = father[i][y];
        }
    }

    if(x == y) {
        return x;
    }

    for(int i = LGMAX; i >= 0; i--) {
        if(father[i][x] != father[i][y]) {
            x = father[i][x];
            y = father[i][y];
        }
    }

    return father[0][x];
}

int main() {

    pre[0] = 1;

    for(int i = 1; i <= NMAX; i++) {
        pre[i] = 2 * pre[i - 1];
        if(pre[i] >= MOD) {
            pre[i] -= MOD;
        }
    }

    fscanf(f,"%d %d",&n,&m);

    for(int i = 1; i <= m; i++) {
        fscanf(f,"%d %d",&edges[i].first,&edges[i].second);
        graph[edges[i].first].push_back(edges[i].second);
        graph[edges[i].second].push_back(edges[i].first);
    }

    get_cycles(1,0);

    for(int i = 1; i <= n; i++) {
        graph[i].clear();
    }

    for(int i = 1; i <= m; i++) {
        edges[i].first = remap[edges[i].first];
        edges[i].second = remap[edges[i].second];
        if(edges[i].first != edges[i].second) {
            graph[edges[i].first].push_back(edges[i].second);
            graph[edges[i].second].push_back(edges[i].first);
        }
    }

    dfs(1,0);

    for(int i = 1; i <= LGMAX; i++) {
        for(int j = 1; j <= n; j++) {
            father[i][j] = father[i - 1][father[i - 1][j]];
        }
    }

    fscanf(f,"%d",&q);

    while(q--) {
        int x,y,z;
        fscanf(f,"%d %d",&x,&y);
        x = remap[x];
        y = remap[y];
        z = lca(x,y);
        int ans = pre[cnt[x] + cnt[y] - 2 * cnt[z] + special[z]];
        fprintf(g,"%d\n",ans);
    }

    fclose(f);
    fclose(g);

    return 0;
}
