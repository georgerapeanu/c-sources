#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

FILE *f = stdin;
FILE *g = stdout;

const int NMAX = 1e5;
const int QMAX = 1e5;
const int LGMAX = 16;
const long long inf = (1LL << 60);

int n,s,q,e;
long long dp[LGMAX + 1][NMAX + 5];
int father[LGMAX + 1][NMAX + 5];
vector<pair<int,int> > graph[NMAX + 5];
pair<int,int> edge[NMAX + 5];

int lin[NMAX + 5],sz;
int st[NMAX + 5];
int dr[NMAX + 5];
long long lvl[NMAX + 5];

void dfs(int nod,int tata) {
    father[0][nod] = tata;
    lin[++sz] = nod;
    st[nod] = sz;

    for(auto it:graph[nod]) {
        if(it.first == tata) {
            continue;
        }
        lvl[it.first] = it.second + lvl[nod];
        dfs(it.first,nod);
        dp[0][nod] = min(dp[0][nod],dp[0][it.first] + it.second);
    }

    dr[nod] = sz;
}

int main() {

    fscanf(f,"%d %d %d %d",&n,&s,&q,&e);

    for(int i = 1; i < n; i++) {
        int a,b,w;
        fscanf(f,"%d %d %d",&a,&b,&w);
        graph[a].push_back({b,w});
        graph[b].push_back({a,w});
        edge[i] = {a,b};
    }

    for(int i = 1; i <= n; i++) {
        dp[0][i] = inf;
    }

    for(int i = 1; i <= s; i++) {
        int x;
        fscanf(f,"%d",&x);
        dp[0][x] = 0;
    }

    dfs(e,0);

    for(int i = 1; i <= n; i++) {
        dp[0][i] -= lvl[i];
    }

    for(int h = 1; h <= LGMAX; h++) {
        for(int i = 1; i <= n; i++) {
            father[h][i] = father[h - 1][father[h - 1][i]];
            if(father[h - 1][i] > 0) {
                dp[h][i] = min(dp[h - 1][i],dp[h - 1][father[h - 1][i]]);
            }
        }
    }

    while(q--) {
        int e,u;
        fscanf(f,"%d %d",&e,&u);

        e = (lvl[edge[e].first] < lvl[edge[e].second] ? edge[e].second:edge[e].first);

        if(st[e] > st[u] || dr[u] > dr[e]) {
            fprintf(g,"escaped\n");
        }
        else {
            int nod = u;
            long long best = inf;
            for(int h = LGMAX; h >= 0; h--) {
                if(father[h][nod] > 0 && st[e] <= st[father[h][nod]] && dr[father[h][nod]] <= dr[e]) {
                    best = min(best,dp[h][nod]);
                    nod = father[h][nod];
                }
            }
            best = min(best,dp[0][nod]);///because dp is from curr node to father exclusive
            best += lvl[u];
            if(best >= inf) {
                fprintf(g,"oo\n");
            }
            else {
                fprintf(g,"%lld\n",best);
            }
        }
    }

    return 0;
}
