#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e4;
const int CMAX = 1e4;

int n,c;
vector<int> tree[NMAX + 5];
long long dp[NMAX + 1][CMAX + 1];
int len[NMAX + 1];
int t[NMAX + 1];
long long tmp[CMAX + 5];

void dfs(int nod){
    len[nod] = 0;
    dp[nod][0] = 0;

    for(auto it:tree[nod]){
        dfs(it);
        
        for(int i = 0;i <= len[nod] + len[it] && i <= c;i++){
            tmp[i] = 1e18;
        }

        for(int i = 0;i <= len[nod];i++){
            for(int j = 0;j <= len[it] && i + j <= c;j++){
                tmp[i + j] = min(tmp[i + j],max(dp[nod][i],dp[it][j]));        
            }
        }

        len[nod] = min(len[nod] + len[it],c);

        for(int i = 0;i <= len[nod];i++){
            dp[nod][i] = tmp[i];
        }
    }

    for(int i = min(len[nod] + 1,c);i >= 0;i--){
        dp[nod][i] += t[nod];
        if(i > 0){
            dp[nod][i] = min(dp[nod][i],dp[nod][i - 1]);
        }
    }
    len[nod]++;
}

int main(){
    
    scanf("%d %d",&n,&c);

    int root;

    for(int i = 1;i <= n;i++){
        int father;
        scanf("%d %d",&father,&t[i]);

        if(father == -1){
            root = i;
        }else{
            father++;
            tree[father].push_back(i);
        }
    }

    dfs(root);

    long long ans = 1e18;

    for(int h = 0;h <= c;h++){
        ans = min(ans,dp[root][h]);
    }

    printf("%lld\n",ans);

    return 0;
}

