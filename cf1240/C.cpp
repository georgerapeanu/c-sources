#include <bits/stdc++.h>

using namespace std;

const int NMAX = 5e5;

int t;
int n,k;
vector<pair<int,int> > graph[NMAX + 5];
long long dp[NMAX + 5][2];
vector<long long>tmp;

void dfs(int nod,int tata,int cost_tata){
    dp[nod][0] = 0;
    dp[nod][1] = cost_tata;

    for(auto it:graph[nod]){
        if(it.first == tata){
            continue;
        }
        dfs(it.first,nod,it.second);
    }

    tmp.clear();

    for(auto it:graph[nod]){
        if(it.first == tata){
            continue;
        }
        tmp.push_back(dp[it.first][1] - dp[it.first][0]);
        dp[nod][0] += dp[it.first][0];
        dp[nod][1] += dp[it.first][0];
    }

    sort(tmp.begin(),tmp.end());
    reverse(tmp.begin(),tmp.end());

    for(int i = 0;i < k && i < (int)tmp.size();i++){
        dp[nod][0] += max(tmp[i],0LL);
    }
    
    for(int i = 0;i < k - 1 && i < (int)tmp.size();i++){
        dp[nod][1] += max(tmp[i],0LL);
    }
}

int main() {

    scanf("%d",&t);

    while(t--){
        scanf("%d %d",&n,&k);

        for(int i = 1;i <= n;i++){
            graph[i].clear();
        }

        for(int i = 1;i < n;i++){
            int u,v,w;
            scanf("%d %d %d",&u,&v,&w);
            graph[u].push_back({v,w});
            graph[v].push_back({u,w});
        }

        dfs(1,0,0);

        printf("%lld\n",dp[1][0]);
    }

    return 0;
}
