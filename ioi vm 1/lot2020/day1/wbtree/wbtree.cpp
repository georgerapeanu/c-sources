#include <bits/stdc++.h>
#include "wbtree.h"

using namespace std;

const int MOD = 1e9 + 7;
const int NMAX = 1e5;;

int add(int a,int b){
    a += b;

    if(a >= MOD){
        a -= MOD;
    }

    return a;
}

int mult(int a,int b){
    return 1LL * a * b % MOD;
}

int n;
vector<pair<int,int>> graph[NMAX + 5];
int k;
int cnt[NMAX + 5];

int ans;

int lst_edge_id = -1;
bool in[2 * NMAX + 5];

void predfs(int nod,int tata,int tata_id){
    bool special_son = false;
    bool special = (cnt[nod] == 1);
    for(auto it:graph[nod]){
        if(it.first == tata){
            continue;
        }
        predfs(it.first,nod,it.second);
        special_son |= (cnt[it.first] > 0);
        cnt[nod] += cnt[it.first];
    }
    if(tata && special_son){
        in[tata_id ^ 1] = true;
    }
    if(cnt[nod] != k){
        in[tata_id] = true;
    }

    for(auto it:graph[nod]){
        if(it.first == tata){
            continue;
        }
        if(cnt[it.first] != 0){
            in[it.second ^ 1] = true;
        }
    }
}

int dp[NMAX + 5];

void dfs(int nod,int tata,int tata_id){
    dp[nod] = 1;
    for(auto it:graph[nod]){
        if(it.first == tata){
            continue;
        }
        dfs(it.first,nod,it.second);
        dp[nod] = mult(dp[nod],dp[it.first]);
    }
    if(tata == 0 || in[tata_id ^ 1]){
        ans = add(ans,dp[nod]);
    }
    if(in[tata_id]){
        dp[nod] = add(dp[nod],1);
    }
}

int solve(int N, std::vector<int> p, std::vector<int> q, std::vector<int> r) {
    n = N;
    for(int i = 0;i < N - 1;i++){
        p[i]++;q[i]++;
        graph[p[i]].push_back({q[i],++lst_edge_id});
        graph[q[i]].push_back({p[i],++lst_edge_id});
    }
    k = (int)r.size();
    for(auto it:r){
        it++;
        cnt[it] = 1;
    }

    ans = add(ans,(k > 0));

    predfs(1,0,-1);
    dfs(1,0,-1);

    return ans;

}
