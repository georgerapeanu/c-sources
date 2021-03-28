#include <bits/stdc++.h>

using namespace std;

const int NMAX = 5000;

int n,k;
int len[NMAX + 5];
int dp[NMAX + 5][NMAX + 5];
int tmp_dp[NMAX + 5];

vector<int> graph[NMAX + 5];

const int MOD = 998244353;

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

void dfs(int nod,int tata){
    len[nod] = 0;
    dp[nod][0] = 1;

    for(auto it:graph[nod]){
        if(it == tata){
            continue;
        }
        dfs(it,nod);
        int cnt_ways = 0;
        for(int i = 0;i <= len[it];i++){
            cnt_ways = add(cnt_ways,dp[it][i]);
        }
        for(int i = 0;i <= k && i <= max(len[nod],1 + len[it]);i++){
            tmp_dp[i] = 0;
        }
        for(int i = 0;i <= len[nod];i++){
            tmp_dp[i] = add(tmp_dp[i],mult(cnt_ways,dp[nod][i]));
            for(int j = 0;j < k - i && j <= len[it];j++){
                tmp_dp[max(i,j + 1)] = add(tmp_dp[max(i,j + 1)],mult(dp[nod][i],dp[it][j])); 
            }
        }
        len[nod] = max(len[nod],len[it] + 1);
        len[nod] = min(len[nod],k);

        for(int i = 0;i <= len[nod];i++){
            dp[nod][i] = tmp_dp[i];
        }
    }
}

int main(){

    scanf("%d %d",&n,&k);

    for(int i = 1;i < n;i++){
        int u,v;
        scanf("%d %d",&u,&v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    dfs(1,0);

    int ans = 0;

    for(int i = 0;i <= len[1];i++){
        ans = add(ans,dp[1][i]);
    }

    printf("%d\n",ans);

    return 0;
}
