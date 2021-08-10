#include "ctree.h"

#include <queue>
#include <algorithm>
#include <cstdio>

using namespace std;

const int NMAX = 3e5;
int n;
vector<int> graph[NMAX + 5];
vector<int> sons[NMAX + 5];
int dp[NMAX + 5];
int weight[NMAX + 5];
int cnt[NMAX + 5];

bool cmp(int a,int b){
    return weight[a] < weight[b];
}

void predfs(int nod,int tata){
    dp[nod] = 0;
    weight[nod] = 1;
    cnt[nod] = 0;

    for(auto it:graph[nod]){
        if(it == tata){
            continue;
        }
        sons[nod].push_back(it);
        predfs(it,nod);
        dp[nod] += dp[it];
        dp[nod]++;
    }

    sort(sons[nod].begin(),sons[nod].end(),cmp);

    while(cnt[nod] < (int)sons[nod].size() && weight[nod] + weight[sons[nod][cnt[nod]]] <= n / 2){
        weight[nod] += weight[sons[nod][cnt[nod]]];
        dp[nod]--;
        cnt[nod]++;
    }
}

void dfs(int nod,int tata,vector<int> &res){
    for(auto it:graph[nod]){
        res[nod] += dp[it];
    }

    int b_dp = dp[nod];
    int b_weight = weight[nod];
    int b_cnt = cnt[nod];

    dp[nod] = 0;
    weight[nod] = 1;
    cnt[nod] = 0;

    for(auto it:graph[nod]){
        dp[nod] += dp[it];
        dp[nod]++;
    }
    
    sort(graph[nod].begin(),graph[nod].end(),cmp);

    while(cnt[nod] < (int)graph[nod].size() && weight[nod] + weight[graph[nod][cnt[nod]]] <= n / 2){
        weight[nod] += weight[graph[nod][cnt[nod]]];
        dp[nod]--;
        cnt[nod]++;
    }
    
    /*printf("debug %d\n",nod);
    for(int i = 0;i < n;i++){
        printf("node %d with %d %d\n",i,dp[i],weight[i]);
    }*/

    for(int i = 0;i < (int)graph[nod].size();i++){
        if(graph[nod][i] == tata){
            continue;
        }
        int it = graph[nod][i];
        dp[nod] -= dp[it];
        if(i < cnt[nod]){
            weight[nod] -= weight[it];
        }else{
            dp[nod]--;
        }

        bool ok = (i < cnt[nod] && cnt[nod] < (int)graph[nod].size() && weight[nod] + weight[graph[nod][cnt[nod]]] <= n / 2);

        if(ok){
            dp[nod]--;
            weight[nod] += weight[graph[nod][cnt[nod]]];
        }

        dfs(it,nod,res);

        if(ok){
            weight[nod] -= weight[graph[nod][cnt[nod]]];
            dp[nod]++;
        }
    
        if(i < cnt[nod]){
            weight[nod] += weight[it];
        }else{
            dp[nod]++;
        }
        dp[nod] += dp[it];
    }

    cnt[nod] = b_cnt;
    weight[nod] = b_weight;
    dp[nod] = b_dp;
}


vector<int> solve(int N, vector<int> x, vector<int> y) {
    n = N;

    for(int i = 0;i < n;i++){
        graph[i].clear();
        sons[i].clear();
    }

    vector<int> res(n, 0);

    for(int i = 0;i < n - 1;i++){
        graph[x[i]].push_back(y[i]);
        graph[y[i]].push_back(x[i]);
    }

    predfs(0,-1);
    dfs(0,-1,res);

    return res;
}
