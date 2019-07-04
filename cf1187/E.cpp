#include <bits/stdc++.h>

using namespace std;

const int NMAX = 3e5;

int n;
int weight[NMAX + 5];
int father[NMAX + 5];
long long cost[NMAX + 5];

vector<int> graph[NMAX + 5];

void predfs(int nod,int tata) {
    father[nod] = tata;
    weight[nod] = 1;
    cost[nod] = 1;

    for(auto it:graph[nod]) {
        if(it == tata) {
            continue;
        }
        predfs(it,nod);
        weight[nod] += weight[it];
        cost[nod] += cost[it];
        cost[nod] += weight[it];
    }
}

long long ans = 0;

void dfs(int nod) {
    ans = max(ans,cost[nod]);

    for(auto it:graph[nod]) {
        if(it == father[nod]) {
            continue;
        }
        cost[nod] -= cost[it];
        cost[nod] -= weight[it];
        cost[it] += cost[nod];
        cost[it] += n - weight[it];
        dfs(it);
        cost[it] -= n - weight[it];
        cost[it] -= cost[nod];
        cost[nod] += weight[it];
        cost[nod] += cost[it];
    }
}

int main() {

    scanf("%d",&n);

    for(int i = 1; i < n; i++) {
        int u,v;
        scanf("%d %d",&u,&v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    predfs(1,0);
    dfs(1);

    printf("%lld\n",ans);

    return 0;
}
