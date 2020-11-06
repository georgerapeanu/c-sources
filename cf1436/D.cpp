#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2e5;

vector<int> graph[NMAX + 5];

int n;
int leaves[NMAX + 5];
long long a[NMAX + 5];
long long weight[NMAX + 5];
long long dp[NMAX + 5];
long long freespace[NMAX + 5];

void predfs(int nod,int tata){
    for(auto it:graph[nod]){
        if(it == tata){
            continue;
        }
        predfs(it,nod);
        weight[nod] += weight[it];
        leaves[nod] += leaves[it];
    }

    leaves[nod] += (graph[nod].size() == (tata != 0) ? 1:0);
}

void dfs(int nod,int tata){
    for(auto it:graph[nod]){
        if(it == tata){
            continue;
        }
        dfs(it,nod);
        dp[nod] = max(dp[nod],dp[it]);
        if(a[nod] >= freespace[it]){
            a[nod] -= freespace[it];
        }
        else{
            freespace[nod] += freespace[it] - a[nod];
            a[nod] = 0;
        }
    }

    for(auto it:graph[nod]){
        if(it == tata){
            continue;
        }
        freespace[nod] += 1LL * (dp[nod] - dp[it]) * leaves[it];
    }

    if(a[nod] >= freespace[nod]){
        a[nod] -= freespace[nod];
        freespace[nod] = 0;
    }
    else{
        freespace[nod] -= a[nod];
        a[nod] = 0;
    }
    
    dp[nod] += (a[nod] / leaves[nod]);
    a[nod] %= leaves[nod];
    if(a[nod] > 0){
        dp[nod]++;
        freespace[nod] += leaves[nod] - a[nod];
    }
}

int main(){

    scanf("%d",&n);

    for(int i = 2;i <= n;i++){
        int nod;
        scanf("%d",&nod);
        graph[i].push_back(nod);
        graph[nod].push_back(i);
    }

    for(int i = 1;i <= n;i++){
        scanf("%lld",&weight[i]);
        a[i] = weight[i];
    }

    predfs(1,0);
    dfs(1,0);
    printf("%lld\n",dp[1]);
    for(int i = 1;i <= n;i++){
        //printf("%lld %lld\n",dp[i],freespace[i]);
    }

    return 0;
}
