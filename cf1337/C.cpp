#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2e5;

vector<int> graph[NMAX + 5];
int lvl[NMAX + 5];
int w[NMAX + 5];
int bst[NMAX + 5];

int n,k;

void dfs(int nod,int tata) {
    lvl[nod] = 1 + lvl[tata];
    w[nod] = 1;
    for(auto it:graph[nod]) {
        if(it == tata) {
            continue;
        }
        dfs(it,nod);
        w[nod] += w[it];
    }
    bst[nod] = (lvl[nod] - 1) - (w[nod] - 1);
}

int main() {

    scanf("%d %d",&n,&k);

    for(int i = 1; i < n; i++) {
        int u,v;
        scanf("%d %d",&u,&v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    dfs(1,0);

    sort(bst + 1,bst + 1 + n);
    reverse(bst + 1,bst + 1 + n);

    long long ans = 0;

    for(int i = 1; i <= k; i++) {
        ans += bst[i];
    }

    printf("%lld\n",ans);

    return 0;
}
