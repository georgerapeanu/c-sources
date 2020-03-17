#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

FILE *f = fopen("sakura.in","r");
FILE *g = fopen("sakura.out","w");

const int NMAX = 500;

int t;
int n,m;
vector<int> sons_a[NMAX + 5];
vector<int> sons_b[NMAX + 5];

int lvl_a[NMAX + 5];
int weight_a[NMAX + 5];
int lvl_b[NMAX + 5];
int weight_b[NMAX + 5];

vector<int> order_a;
vector<int> order_b;

bool dp[NMAX + 5][NMAX + 5];

void dfs1(int nod,int tata) {
    lvl_a[nod] = 1 + lvl_a[tata];
    weight_a[nod] = 1;

    for(auto &it:sons_a[nod]) {
        if(it == tata) {
            swap(it,sons_a[nod].back());
            break;
        }
    }

    if(tata > 0) {
        sons_a[nod].pop_back();
    }

    for(auto it:sons_a[nod]) {
        dfs1(it,nod);
        weight_a[nod] += weight_a[it];
    }
    order_a.push_back(nod);
}

void dfs2(int nod,int tata) {
    lvl_b[nod] = 1 + lvl_b[tata];
    weight_b[nod] = 1;

    for(auto &it:sons_b[nod]) {
        if(it == tata) {
            swap(it,sons_b[nod].back());
            break;
        }
    }

    if(tata > 0) {
        sons_b[nod].pop_back();
    }

    for(auto it:sons_b[nod]) {
        dfs2(it,nod);
        weight_b[nod] += weight_b[it];
    }
    order_b.push_back(nod);
}

vector<int> graph[NMAX + 5];

int l[NMAX + 5];
int r[NMAX + 5];
bool viz[NMAX + 5];

bool match(int node) {
    if(viz[node]) {
        return false;
    }

    viz[node] = true;

    for(auto it:graph[node]) {
        if(r[it] == 0) {
            l[node] = it;
            r[it] = node;
            return true;
        }
    }

    for(auto it:graph[node]) {
        if(match(r[it])) {
            l[node] = it;
            r[it] = node;
            return true;
        }
    }

    return false;
}

bool process(int r1,int r2) {
    for(auto it:sons_a[r1]) {
        l[it] = 0;
        graph[it].clear();
    }
    for(auto it2:sons_b[r2]) {
        r[it2] = 0;
    }

    for(auto it:sons_a[r1]) {
        for(auto it2:sons_b[r2]) {
            if(dp[it][it2] == true) {
                graph[it].push_back(it2);
            }
        }
    }

    int cuplaj = 0;
    bool ok = true;

    while(ok) {
        ok = false;
        for(auto it:sons_a[r1]) {
            viz[it] = false;
        }
        for(auto it:sons_a[r1]) {
            if(l[it] == 0 && match(it)) {
                ok = true;
                cuplaj++;
            }
        }
    }

    return cuplaj == (int)sons_b[r2].size();
}

int main() {

    fscanf(f,"%d",&t);

    while(t--) {
        fscanf(f,"%d",&n);
        for(int i = 1; i <= n; i++) {
            sons_a[i].clear();
        }
        for(int i = 1; i < n; i++) {
            int u,v;
            fscanf(f,"%d %d",&u,&v);
            u++;
            v++;
            sons_a[u].push_back(v);
            sons_a[v].push_back(u);
        }
        fscanf(f,"%d",&m);
        for(int i = 1; i <= m; i++) {
            sons_b[i].clear();
        }
        for(int i = 1; i < m; i++) {
            int u,v;
            fscanf(f,"%d %d",&u,&v);
            u++;
            v++;
            sons_b[u].push_back(v);
            sons_b[v].push_back(u);
        }

        if(n < m) {
            fprintf(g,"-1\n");
            continue;
        }

        order_a.clear();
        order_b.clear();

        dfs1(1,0);
        dfs2(1,0);

        for(auto it:order_a) {
            for(auto it2:order_b) {
                if(weight_a[it] < weight_b[it2]) {
                    dp[it][it2] = 0;
                    continue;
                }
                dp[it][it2] = process(it,it2);
            }
        }

        if(dp[1][1] == 1) {
            fprintf(g,"%d\n",n - m);
        }
        else {
            fprintf(g,"-1\n");
        }
    }

    return 0;
}
