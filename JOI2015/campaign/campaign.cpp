#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int NMAX = 1e5;
const int LGMAX = 17;

int n,q;
vector<int> graph[NMAX + 5];
vector<pair<pair<int,int>,int> > paths[NMAX + 5];

int lvl[NMAX + 5];
int fst[NMAX + 5];
int lst[NMAX + 5];
int last;

int father[LGMAX + 1][NMAX + 5];

int dp[NMAX + 5];
int aib[NMAX + 5];

void update(int pos,int val) {
    for(; pos <= n; pos += (-pos) & pos) {
        aib[pos] += val;
    }
}

int query(int pos) {
    int ans = 0;
    for(; pos; pos -= (-pos) & pos) {
        ans += aib[pos];
    }
    return ans;
}

void dfs(int nod,int tata) {
    father[0][nod] = tata;
    lvl[nod] = 1 + lvl[tata];
    fst[nod] = ++last;

    for(auto it:graph[nod]) {
        if(it == tata) {
            continue;
        }
        dfs(it,nod);
    }

    lst[nod] = last;
}

void make_lca() {
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

    int diff = (lvl[y] - lvl[x]);

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

void dfs2(int nod,int tata) {

    int tmp = 0;
    for(auto it:graph[nod]) {
        if(it == tata) {
            continue;
        }
        dfs2(it,nod);
        tmp += dp[it];
    }


    dp[nod] = tmp;

    for(auto it:graph[nod]) {
        if(it == tata) {
            continue;
        }
        update(fst[it],-dp[it]);
        update(lst[it] + 1,dp[it]);
    }

    for(auto it:paths[nod]) {
        dp[nod] = max(dp[nod],tmp + query(fst[it.first.first]) + query(fst[it.first.second]) + it.second);
    }

    update(fst[nod],tmp);
    update(lst[nod] + 1,-tmp);
}

int main() {

    scanf("%d",&n);

    for(int i = 1; i < n; i++) {
        int x,y;
        scanf("%d %d",&x,&y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    dfs(1,0);
    make_lca();

    scanf("%d",&q);

    while(q--) {
        int a,b,c;
        scanf("%d %d %d",&a,&b,&c);
        paths[lca(a,b)].push_back({{a,b},c});
    }

    dfs2(1,0);

    printf("%d\n",dp[1]);

    return 0;
}
