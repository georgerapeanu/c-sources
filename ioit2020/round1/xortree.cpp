#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2e5;

int n;

vector<int> graph[NMAX + 5];
long long dp[NMAX + 5][2];
int val[NMAX + 5];

void dfs(int nod,int tata){
    dp[nod][0] = 0;
    dp[nod][1] = -1e18;
    for(auto it:graph[nod]){
        if(it == tata){
            continue;
        }
        dfs(it,nod);
        long long new_dp[2];
        new_dp[0] = max(dp[nod][0] + dp[it][0],dp[nod][1] + dp[it][1]);
        new_dp[1] = max(dp[nod][0] + dp[it][1],dp[nod][1] + dp[it][0]);

        dp[nod][0] = new_dp[0];
        dp[nod][1] = new_dp[1];
    }

    if(graph[nod].size() == (tata > 0)){
        dp[nod][0] = 0;
        dp[nod][1] = 0;
    }

    dp[nod][0] += val[nod];

}

int main(){

    scanf("%d",&n);

    for(int i = 1;i < n;i++){
        int u,v;
        scanf("%d %d",&u,&v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    for(int i = 1;i <= n;i++){
        scanf("%d",&val[i]);
    }

    dfs(1,0);

    printf("%lld\n",max(dp[1][0],dp[1][1]));

    return 0;
}
